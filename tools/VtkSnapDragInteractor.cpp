#include "VtkSnapDragInteractor.h"
#include "VtkMarkerHandler.h"
#include "VtkSplineHandler.h"
#include "components/Marker.h"
#include <vtkRenderWindow.h>

void VtkSnapDragInteractor::OnLeftButtonDown(){
    int* pos = this->GetInteractor()->GetEventPosition();
    Picker->Pick(pos[0], pos[1], 0, this->GetDefaultRenderer());

    vtkActor* pickedActor = Picker->GetActor();

    // Check if picked actor is one of our spheres and find the corresponding marker
    if (MarkerHandler) {
        for (auto& marker : MarkerHandler->getMarkers()) {
            if (pickedActor == marker->getActor()) {
                ActiveSphere = pickedActor;
                ActiveMarker = marker;
                dragging = true;
                // Don't call parent's OnLeftButtonDown to prevent camera rotation while dragging
                return;
            }
        }
    }
    
    // If no marker was picked, allow normal camera interaction
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void VtkSnapDragInteractor::OnLeftButtonUp(){
    if (dragging && OnMarkerMovedCallback) {
        // Notify that marker movement is complete
        OnMarkerMovedCallback();
    }
    
    dragging = false;
    ActiveSphere = nullptr;
    ActiveMarker = nullptr;
    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void VtkSnapDragInteractor::OnMouseMove(){
    if (dragging && ActiveSphere && ActiveMarker && TargetActor) {
        int* pos = this->GetInteractor()->GetEventPosition();
        Picker->Pick(pos[0], pos[1], 0, this->GetDefaultRenderer());

        // Pick on the target surface (main object)
        if (Picker->GetActor() == TargetActor) {
            double pickedPos[3];
            Picker->GetPickPosition(pickedPos);
            
            // Update the marker's position (this updates the sphere source center)
            ActiveMarker->setPosition(pickedPos[0], pickedPos[1], pickedPos[2]);
            ActiveMarker->Update(); // Update the sphere source
            
            // Update spline in real-time if handler is available
            if (SplineHandler && MarkerHandler) {
                SplineHandler->updateSpline(MarkerHandler->getMarkers());
                SplineHandler->renderSpline();
            }
            
            // Request a render
            this->GetInteractor()->GetRenderWindow()->Render();
        }
        return; // Don't call parent's OnMouseMove to prevent camera rotation
    }
    
    // If not dragging, allow normal camera interaction
    vtkInteractorStyleTrackballCamera::OnMouseMove();
}