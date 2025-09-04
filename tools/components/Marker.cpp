#include "Marker.h"
#include <vtkPolyDataMapper.h>

Marker::Marker(double x, double y, double z, double radius) {
    this->SetCenter(x, y, z);
    this->SetRadius(radius);
    this->SetThetaResolution(16);
    this->SetPhiResolution(16);
    this->Update();

    actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(this->GetOutputPort());
    actor->SetMapper(mapper);
}

Marker::Marker() : Marker(0.0, 0.0, 0.0, 1.0) {}

vtkSmartPointer<vtkActor> Marker::getActor() {
    return actor;
}

void Marker::setPosition(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->SetCenter(x, y, z);
}

std::vector<double> Marker::getPosition() {
    return {x, y, z};
}

void Marker::setRadius(double radius) {
    this->radius = radius;
    this->SetRadius(radius);
}
