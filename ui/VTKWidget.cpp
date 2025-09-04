#include "VTKWidget.h"
#include <vtk-9.1/vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <QDebug>
#include "../tools/SplineCropTool.h"
#include <vtkConnectivityFilter.h>
#include <vtkPolyDataConnectivityFilter.h>
#include "../tools/VtkSnapDragInteractor.h"


vtkStandardNewMacro(VtkSnapDragInteractor);

VTKWidget::VTKWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    this->setRenderWindow(renderWindow);
    renderer = vtkSmartPointer<vtkRenderer>::New();
    this->renderWindow()->AddRenderer(renderer);
    
    this->cellPicker = vtkSmartPointer<vtkCellPicker>::New();
    this->markerHandler = new VtkMarkerHandler(renderer);
    this->splineHandler = new VtkSplineHandler(renderer);
    // Set up the interactor with handlers
    snapDragInteractor->SetMarkerHandler(markerHandler);
    snapDragInteractor->SetSplineHandler(splineHandler);
    
    initializeScene();
}

vtkSmartPointer<vtkRenderer> VTKWidget::getRenderer() {
    return renderer;
}

void VTKWidget::setPolyDataFromFileManager(vtkSmartPointer<vtkPolyData> data) {
    if (data) {
        this->polyData = data;
        initializeScene();
        this->renderWindow()->Render();
    }
}

void VTKWidget::initializeScene() {
    if (!renderer) {
        renderer = vtkSmartPointer<vtkRenderer>::New();
        this->renderWindow()->AddRenderer(renderer);
    }
    // Remove all previous actors
    renderer->RemoveAllViewProps();

    // Set background color dark blue
    renderer->SetBackground(0.1, 0.1, 0.3);

    // Add ambient-like light for global illumination
    vtkSmartPointer<vtkLight> ambientLight = vtkSmartPointer<vtkLight>::New();
    ambientLight->SetLightTypeToSceneLight();
    renderer->AutomaticLightCreationOff();
    if(polyData){
    // Compute normals for smooth shading
    vtkSmartPointer<vtkPolyDataNormals> normals = vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetInputData(polyData);
    normals->ConsistencyOn();
    normals->SplittingOff();
    normals->AutoOrientNormalsOn();
    normals->ComputePointNormalsOn();
    normals->ComputeCellNormalsOff();
    normals->Update();
    vtkSmartPointer<vtkPolyData> smoothPolyData = normals->GetOutput();

    actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(smoothPolyData);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetAmbient(0.3);
    actor->GetProperty()->SetDiffuse(0.7);
    actor->GetProperty()->SetSpecular(0.1);
    actor->GetProperty()->SetInterpolationToPhong();
    renderer->AddActor(actor);
    vtkSmartPointer<vtkLight> headLight = vtkSmartPointer<vtkLight>::New();
    headLight->SetLightTypeToHeadlight();
    headLight->SetIntensity(0.75);
    renderer->AddLight(headLight);
    }

    // Set Camera
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    // Center the camera on the actor's bounding box and set a suitable distance
    double bounds[6] = {0,0,0,0,0,0};
    if (polyData) {
        polyData->GetBounds(bounds);
        double center[3] = {
            (bounds[0] + bounds[1]) / 2.0,
            (bounds[2] + bounds[3]) / 2.0,
            (bounds[4] + bounds[5]) / 2.0
        };
        double radius = std::max({bounds[1] - bounds[0], bounds[3] - bounds[2], bounds[5] - bounds[4]}) * 0.5;
        double distance = radius * 2.5; // Adjust multiplier for zoom level

        camera->SetFocalPoint(center);
        camera->SetPosition(center[0], center[1], center[2] + distance);
        camera->SetViewUp(0, 1, 0);
    } else {
        camera->SetPosition(0, 0, 1);
        camera->SetFocalPoint(0, 0, 0);
        camera->SetViewUp(0, 1, 0);
    }
    renderer->SetActiveCamera(camera);

    //Set Scene
    if (polyData) {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(polyData);
        actor->SetMapper(mapper);
        // Increase ambient property for the actor's material
        actor->GetProperty()->SetAmbient(0.15);
        actor->GetProperty()->SetDiffuse(0.5);
        actor->GetProperty()->SetSpecular(0.1);
        renderer->AddActor(actor);
        qDebug() << "Points: " << polyData->GetNumberOfPoints();
        qDebug() << "Polys: " << polyData->GetNumberOfPolys();
    }
    snapDragInteractor->SetDefaultRenderer(renderer);
    snapDragInteractor->TargetActor = this->actor; // Set the target actor for snapping
    this->renderWindow()->GetInteractor()->SetInteractorStyle(snapDragInteractor);
    // Don't call interactor->Start() in Qt applications
}


void VTKWidget::mousePressEvent(QMouseEvent* event) {
    if (isMarkerEnabled) {
        int x = event->pos().x();
        int y = this->height() - event->pos().y();
        cellPicker->Pick(x, y, 0, renderer);
        double pickedPos[3];
        cellPicker->GetPickPosition(pickedPos);
        qDebug() << "Picked Position:" << pickedPos[0] << pickedPos[1] << pickedPos[2];
        if (cellPicker->GetCellId() >= 0) {
            markerHandler->addMarker(pickedPos[0], pickedPos[1], pickedPos[2], 5);
            qDebug() << "Marker added at: " << pickedPos[0] << pickedPos[1] << pickedPos[2];
        
            if(splineDrawingForCropEnabled){
                if(splineHandler->getSpline() == nullptr){
                    splineHandler->createSpline(splineHandler->calculateSplinePoints(markerHandler->getMarkers()));
                }else{
                    qDebug() << "Updating Spline with markers count: " << markerHandler->getMarkers().size();
                    splineHandler->updateSpline(markerHandler->getMarkers());
                }
                splineHandler->renderSpline();
                
            }
        }
        // The interactor now uses MarkerHandler directly, no need to manage SphereActors
        this->renderWindow()->Render();
    }
}



void VTKWidget::toggleSnapMode(){
    if(markerHandler->getMarkers().size() > 3){
        // First, clear existing markers to avoid duplicates
        markerHandler->clearMarkers();
        
        // Add extra points for snapping
        splineHandler->addExtraPointsForSnap(this->polyData);
        
        // Create new markers for all points in the updated spline
        for (int i = 0; i < splineHandler->getSpline()->GetPoints()->GetNumberOfPoints(); i++)
        {
            double* point = splineHandler->getSpline()->GetPoints()->GetPoint(i);
            markerHandler->addMarker(point[0], point[1], point[2], 2.5);
        }
        
        // Update the spline with the new markers
        splineHandler->updateSpline(markerHandler->getMarkers());
        splineHandler->renderSpline();
        
        // Render the changes
        this->renderWindow()->Render();
    }
    this->setIsMarkerEnabled(false);
    this->setSplineDrawingForCropEnabled(false);
}

void VTKWidget::toggleResetCropMarker() {
    if(splineHandler && markerHandler) {
        splineHandler->clearSpline();
        markerHandler->clearMarkers();
        this->renderWindow()->Render();
    }
}

void VTKWidget::toggleApplySplineCrop() {
    if (splineHandler && markerHandler && polyData) {
        this->cropTool = new SplineCropTool();
        cropTool->setSplinePolyData(splineHandler->getSplineAsPolydata());
        cropTool->setObjectWillBeClipped(this->polyData);
        cropTool->setRenderer(renderer);
        cropTool->clipSplineWithPolyData();
        polyData = cropTool->GetOutput();
        renderer->RemoveAllViewProps();

        vtkSmartPointer<vtkConnectivityFilter> connectivityFilter = vtkSmartPointer<vtkConnectivityFilter>::New();
        connectivityFilter->SetInputData(polyData);
        connectivityFilter->SetExtractionModeToAllRegions();
        connectivityFilter->Update();
        int numRegions = connectivityFilter->GetNumberOfExtractedRegions();
        qDebug() << "Region count: " << numRegions;
        auto connRegion0 = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
        connRegion0->SetInputData(polyData);
        connRegion0->SetExtractionModeToSpecifiedRegions();
        connRegion0->InitializeSpecifiedRegionList();
        int region = 0;
        if(numRegions > 1){
            region = 1;
        }
        connRegion0->AddSpecifiedRegion(region);
        connRegion0->Update();
        polyData = connRegion0->GetOutput();
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(polyData);
        actor->SetMapper(mapper);
        renderer->AddActor(actor);
        this->renderWindow()->Render();
    }
}

