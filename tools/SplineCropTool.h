#pragma once
#include <vtkClipPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkTubeFilter.h>
#include <vtkImplicitPolyDataDistance.h>
#include <vtkRenderer.h>

class SplineCropTool: public vtkClipPolyData{
public:
    SplineCropTool();
    ~SplineCropTool();
    void setSplinePolyData(vtkSmartPointer<vtkPolyData> polyData);
    vtkSmartPointer<vtkPolyData> getSplinePolyData() const { return splinePolyData; }
    vtkSmartPointer<vtkPolyData> getObjectWillBeClipped() const { return objectWillBeClipped; }
    void setObjectWillBeClipped(vtkSmartPointer<vtkPolyData> polyData) { objectWillBeClipped = polyData; }
    void setRenderer(vtkSmartPointer<vtkRenderer> renderer) { this->renderer = renderer; }
    void clipSplineWithPolyData();
    void renderChanges(vtkSmartPointer<vtkRenderer> renderer);
    vtkAlgorithmOutput* getOutputPort() { return this->GetOutputPort(); }

private:
    vtkSmartPointer<vtkPolyData> splinePolyData;
    vtkSmartPointer<vtkPolyData> clippedOutput;
    vtkSmartPointer<vtkPolyData> objectWillBeClipped;
    vtkSmartPointer<vtkTubeFilter> tube;
    vtkSmartPointer<vtkImplicitPolyDataDistance> implicitDistance;
    vtkSmartPointer<vtkRenderer> renderer;
    void sourceToTubeFilter();
    void updateImplicitFunction();
};