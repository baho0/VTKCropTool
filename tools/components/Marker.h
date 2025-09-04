#pragma once

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

class Marker: public vtkSphereSource {
public:
    static Marker* New() { return new Marker(); }
    Marker();
    Marker(double x, double y, double z, double radius);
    vtkSmartPointer<vtkActor> getActor();
    void setPosition(double x, double y, double z);
    std::vector<double> getPosition();
    void setRadius(double radius);
private:
    double radius;
    double x;
    double y;
    double z;
    vtkSmartPointer<vtkActor> actor;

    // Prevent copying and assignment
    Marker(const Marker&) = delete;
    void operator=(const Marker&) = delete;
};

