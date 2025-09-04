#include "VtkMarkerHandler.h"

VtkMarkerHandler::VtkMarkerHandler(vtkSmartPointer<vtkRenderer> renderer)
    : renderer(renderer) {}

void VtkMarkerHandler::addMarker(double x, double y, double z, double radius) {
    vtkSmartPointer<Marker> marker = vtkSmartPointer<Marker>::New();
    marker->setPosition(x, y, z);
    marker->setRadius(radius);
    markers.push_back(marker);
    renderer->AddActor(marker->getActor());
}

void VtkMarkerHandler::removeMarker(int id) {
    if (id >= 0 && id < markers.size()) {
        renderer->RemoveActor(markers[id]->getActor());
        markers.erase(markers.begin() + id);
    }
}

void VtkMarkerHandler::clearMarkers() {
    for (auto& marker : markers) {
        renderer->RemoveActor(marker->getActor());
    }
    markers.clear();
}
