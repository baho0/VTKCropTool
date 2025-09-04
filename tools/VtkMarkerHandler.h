#pragma once

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include "components/Marker.h"

class VtkMarkerHandler {
public:
    VtkMarkerHandler(vtkSmartPointer<vtkRenderer> renderer);
    void addMarker(double x, double y, double z, double radius);
    void removeMarker(int id);
    void clearMarkers();
    std::vector<vtkSmartPointer<Marker>>& getMarkers() { return markers; }

private:
    vtkSmartPointer<vtkRenderer> renderer;
    std::vector<vtkSmartPointer<Marker>> markers;
};
