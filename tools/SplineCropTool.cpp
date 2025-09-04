#include "SplineCropTool.h"
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>

SplineCropTool::SplineCropTool() {
    this->splinePolyData = nullptr;
    this->SetInsideOut(false); // Keep the outside part
    this->SetGenerateClippedOutput(false); // We only want the clipped part
}

SplineCropTool::~SplineCropTool() = default;

void SplineCropTool::clipSplineWithPolyData() {
    if (!splinePolyData && !objectWillBeClipped && !implicitDistance && !renderer) return;
    this->SetInputData(objectWillBeClipped);
    this->SetClipFunction(implicitDistance);
    this->Update();
}

void SplineCropTool::sourceToTubeFilter() {
    if (!splinePolyData) return;

    tube = vtkSmartPointer<vtkTubeFilter>::New();
    tube->SetInputData(splinePolyData);
    tube->SetRadius(1.5);
    tube->SetNumberOfSides(100);
    tube->Update();
}

void SplineCropTool::updateImplicitFunction() {
    if (!tube) return;

    implicitDistance = vtkSmartPointer<vtkImplicitPolyDataDistance>::New();
    implicitDistance->SetInput(tube->GetOutput());
}

void SplineCropTool::renderChanges(vtkSmartPointer<vtkRenderer> renderer) {
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(this->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
}

void SplineCropTool::setSplinePolyData(vtkSmartPointer<vtkPolyData> polyData) {
    splinePolyData = polyData;
    sourceToTubeFilter();
    updateImplicitFunction();
}
