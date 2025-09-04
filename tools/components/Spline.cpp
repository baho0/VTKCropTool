#include "Spline.h"
#include <vtkCardinalSpline.h>
#include <vtkKochanekSpline.h>
#include <vtkPointLocator.h>
#include <qdebug.h>
#include <set>

Spline::Spline(vtkSmartPointer<vtkPoints> points) : points(points) {

    // Set Spline properties
    this->Closed = true; // Whether the spline is closed
    this->SetLeftConstraint(0);
    this->SetRightConstraint(0);
    this->SetLeftValue(0.0);
    this->SetRightValue(0.0);

}

Spline::~Spline() = default;

void Spline::generateSpline(){
    if (this->points != nullptr && this->points->GetNumberOfPoints() >= 2)
    {
        this->SetPoints(this->points);
        
        // Cardinal Spline
        //this->SetXSpline(vtkSmartPointer<vtkCardinalSpline>::New());
        //this->SetYSpline(vtkSmartPointer<vtkCardinalSpline>::New());
        //this->SetZSpline(vtkSmartPointer<vtkCardinalSpline>::New());
    
        // Kochanek-Bartels Spline
        this->xSpline = vtkSmartPointer<vtkKochanekSpline>::New();
        xSpline->SetDefaultBias(0);
        xSpline->SetDefaultTension(0);
        xSpline->SetDefaultContinuity(0);

        this->ySpline = vtkSmartPointer<vtkKochanekSpline>::New();
        ySpline->SetDefaultBias(0);
        ySpline->SetDefaultTension(0);
        ySpline->SetDefaultContinuity(0);

        this->zSpline = vtkSmartPointer<vtkKochanekSpline>::New();
        zSpline->SetDefaultBias(0);
        zSpline->SetDefaultTension(0);
        zSpline->SetDefaultContinuity(0);

        this->SetXSpline(xSpline);
        this->SetYSpline(ySpline);
        this->SetZSpline(zSpline);
    }
}

void Spline::updateSpline(){
    if (this->points != nullptr && this->points->GetNumberOfPoints() >= 2)
    {
        this->SetPoints(this->points);
        this->Modified();
    }
}

void Spline::clearSpline(){
    if (this->points != nullptr)
    {
        this->points->Reset();
        this->SetPoints(this->points);
        this->Modified();
    }
}

void Spline::closeSpline(){
    this->Closed = true;
    this->Modified();
}

void Spline::addExtraPointsForSnap(vtkPolyData* polyData) {
    if (!this->points || !polyData) return;

    vtkSmartPointer<vtkPointLocator> pointLocator = vtkSmartPointer<vtkPointLocator>::New();
    pointLocator->SetDataSet(polyData);
    pointLocator->BuildLocator();

    vtkSmartPointer<vtkPoints> snappedPoints = vtkSmartPointer<vtkPoints>::New();
    std::set<std::tuple<double,double,double>> uniquePoints;

    for (double u = 0.0; u <= 1.0; u += 0.05) {
        double pt[3];
        this->Evaluate(&u, pt, nullptr);

        vtkIdType nearestId = pointLocator->FindClosestPoint(pt);
        if (nearestId != -1) {
            double snapped[3];
            polyData->GetPoints()->GetPoint(nearestId, snapped);

            std::tuple<double,double,double> key = 
                std::make_tuple(round(snapped[0]*1e6)/1e6,
                                round(snapped[1]*1e6)/1e6,
                                round(snapped[2]*1e6)/1e6);

            if (uniquePoints.find(key) == uniquePoints.end()) {
                snappedPoints->InsertNextPoint(snapped);
                uniquePoints.insert(key);
                qDebug() << "Snapped Point:" << snapped[0] << snapped[1] << snapped[2];
            }
        }
    }
    this->points = snappedPoints;
    this->updateSpline();
}
