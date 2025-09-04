#pragma once
#include <QWidget>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkCellPicker.h>
#include <QMouseEvent>
#include "../tools/VtkMarkerHandler.h"
#include "../tools/VtkSplineHandler.h"
#include "../tools/SplineCropTool.h"
#include "../tools/VtkSnapDragInteractor.h"
#include <vtkRenderWindowInteractor.h>


class VTKWidget : public QVTKOpenGLNativeWidget {
    Q_OBJECT
public:
    VTKWidget(QWidget* parent = nullptr);
    vtkSmartPointer<vtkRenderer> getRenderer();
    void setPolyDataFromFileManager(vtkSmartPointer<vtkPolyData> data);

    //Get-Set
    bool getIsMarkerEnabled() const { return isMarkerEnabled; }
    void setIsMarkerEnabled(bool enabled) { isMarkerEnabled = enabled; }
    bool getSplineDrawingForCropEnabled() const { return splineDrawingForCropEnabled; }
    void setSplineDrawingForCropEnabled(bool enabled) { splineDrawingForCropEnabled = enabled; }

    //Toggle Buttons
    void toggleResetCropMarker();
    void toggleApplySplineCrop();
    void toggleSnapMode();
private:
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkPolyData> polyData;
    vtkSmartPointer<vtkCellPicker> cellPicker;
    bool isMarkerEnabled = false;
    bool splineDrawingForCropEnabled = false;
    VtkMarkerHandler* markerHandler;
    VtkSplineHandler* splineHandler;
    SplineCropTool* cropTool;
    vtkNew<VtkSnapDragInteractor> snapDragInteractor;
    vtkSmartPointer<vtkActor> actor;
    vtkNew<vtkRenderWindowInteractor> interactor;
    void initializeScene();
    void mousePressEvent(QMouseEvent* event) override;
};
