#pragma once 
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include "components/Spline.h"
#include "VtkMarkerHandler.h"
#include <vtkRenderer.h>
#include <vector>
#include <vtkPolyData.h>
#include <vtkParametricFunctionSource.h>
#include <vtkActor.h>

class VtkSplineHandler{
public:
    VtkSplineHandler(vtkSmartPointer<vtkRenderer> renderer);
    ~VtkSplineHandler();

    void createSpline(vtkSmartPointer<vtkPoints> points);
    void updateSpline(const std::vector<vtkSmartPointer<Marker>>& markers);
    void clearSpline();
    void closeSpline();
    void renderSpline();
    Spline* getSpline() const { return spline; }
    vtkSmartPointer<vtkPoints> getPoints() const { return points; }
    const std::vector<vtkSmartPointer<Marker>>& getMarkers() const { return markers; }
    void setMarkers(const std::vector<vtkSmartPointer<Marker>>& markers) { this->markers = markers; }
    vtkSmartPointer<vtkPoints> calculateSplinePoints(const std::vector<vtkSmartPointer<Marker>>& markers);
    vtkSmartPointer<vtkPolyData> getSplineAsPolydata();
    void addExtraPointsForSnap(vtkPolyData* polyData);
private:
    Spline* spline = nullptr;
    vtkSmartPointer<vtkPoints> points;
    std::vector<vtkSmartPointer<Marker>> markers;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkParametricFunctionSource> source = nullptr;
    vtkSmartPointer<vtkActor> splineActor = nullptr; // Track the spline's visual actor
};