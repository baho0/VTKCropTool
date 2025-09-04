#pragma once
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCellPicker.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderWindowInteractor.h>
#include <functional>

// Forward declarations
class VtkMarkerHandler;
class VtkSplineHandler;
class Marker;

class VtkSnapDragInteractor: public vtkInteractorStyleTrackballCamera {
public:
    static VtkSnapDragInteractor* New();
    vtkTypeMacro(VtkSnapDragInteractor, vtkInteractorStyleTrackballCamera);

    vtkActor* TargetActor = nullptr;
    vtkSmartPointer<vtkCellPicker> Picker = vtkSmartPointer<vtkCellPicker>::New();

    // Add marker and spline handlers
    VtkMarkerHandler* MarkerHandler = nullptr;
    VtkSplineHandler* SplineHandler = nullptr;

    vtkActor* ActiveSphere = nullptr;
    vtkSmartPointer<Marker> ActiveMarker = nullptr;
    bool dragging = false;

    // Callback for when marker is moved
    std::function<void()> OnMarkerMovedCallback = nullptr;

    void OnLeftButtonDown() override;
    void OnLeftButtonUp() override;
    void OnMouseMove() override;

    void SetMarkerHandler(VtkMarkerHandler* handler) { MarkerHandler = handler; }
    void SetSplineHandler(VtkSplineHandler* handler) { SplineHandler = handler; }
    
private:
};