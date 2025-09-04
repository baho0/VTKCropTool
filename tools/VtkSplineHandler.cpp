#include "VtkSplineHandler.h"
#include <vtkParametricFunctionSource.h>
#include <vtkParametricFunction.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <qdebug.h>


VtkSplineHandler::VtkSplineHandler(vtkSmartPointer<vtkRenderer> renderer) {
    this->points = vtkSmartPointer<vtkPoints>::New();
    this->markers = std::vector<vtkSmartPointer<Marker>>();
    this->renderer = renderer;
    this->spline = nullptr;
}

VtkSplineHandler::~VtkSplineHandler() {
    // Remove spline actor from renderer if it exists
    if (splineActor && renderer) {
        renderer->RemoveActor(splineActor);
        splineActor = nullptr;
    }
    
    if (spline) {
        delete spline;
        spline = nullptr;
    }
}

void VtkSplineHandler::createSpline(vtkSmartPointer<vtkPoints> points) {
    if (spline) {
        delete spline;
        spline = nullptr;
    }
    this->points = points;
    this->spline = new Spline();
    this->spline->setNewPoints(points);
    this->spline->generateSpline();
}

void VtkSplineHandler::updateSpline(const std::vector<vtkSmartPointer<Marker>>& markers) {
    if (spline) {
        this->markers = markers;
        this->points = calculateSplinePoints(markers);
        this->spline->setNewPoints(this->points);
        this->spline->updateSpline();
    }
}

void VtkSplineHandler::clearSpline() {
    if (spline) {
        this->markers = {};
        this->points = vtkSmartPointer<vtkPoints>::New();
        this->spline->clearSpline();
        
        // Remove the spline actor from the renderer
        if (splineActor) {
            renderer->RemoveActor(splineActor);
            splineActor = nullptr;
        }
        
        // Trigger a render to update the window
        renderer->Render();
    }
}

void VtkSplineHandler::closeSpline() {
    if (spline) {
        this->spline->closeSpline();
    }
}

void VtkSplineHandler::renderSpline(){
    if(!spline) return;
    vtkSmartPointer<vtkPoints> pts = spline->getPoints();
    if (!pts || pts->GetNumberOfPoints() < 2) {
        qDebug() << "Not enough points to render the spline.";
        // Remove existing spline actor if it exists
        if (splineActor) {
            renderer->RemoveActor(splineActor);
            splineActor = nullptr;
        }
        return;
    }
    
    spline->SetPoints(pts);
    for (int i = 0; i < pts->GetNumberOfPoints(); ++i) {
        double p[3];
        pts->GetPoint(i, p);
        qDebug() << "Point" << i << ":" << p[0] << p[1] << p[2];
    }
    
    // Remove previous spline actor if it exists
    if (splineActor) {
        renderer->RemoveActor(splineActor);
        splineActor = nullptr;
    }
    
    source = vtkSmartPointer<vtkParametricFunctionSource>::New();
    source->SetParametricFunction(spline);
    source->SetUResolution(100);
    source->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(source->GetOutputPort());

    // Create new actor and store reference
    splineActor = vtkSmartPointer<vtkActor>::New();
    splineActor->SetMapper(mapper);
    splineActor->GetProperty()->SetLineWidth(3.5);
    splineActor->GetProperty()->SetColor(0.0, 1.0, 0.0); // Green
    renderer->AddActor(splineActor);
}

void VtkSplineHandler::addExtraPointsForSnap(vtkPolyData* polyData) {
    if (spline) {
        spline->addExtraPointsForSnap(polyData);
    }
}

vtkSmartPointer<vtkPoints> VtkSplineHandler::calculateSplinePoints(const std::vector<vtkSmartPointer<Marker>>& markers) {
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    for (const auto& marker : markers) {
        double pos[3];
        pos[0] = marker->getPosition()[0];
        pos[1] = marker->getPosition()[1];
        pos[2] = marker->getPosition()[2];
        points->InsertNextPoint(pos);
    }
    return points;
}

vtkSmartPointer<vtkPolyData> VtkSplineHandler::getSplineAsPolydata() {
    if (spline) {
        return source->GetOutput();
    }
    return nullptr;
}
