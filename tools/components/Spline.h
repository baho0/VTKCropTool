#pragma once
#include <vtkSmartPointer.h>
#include <vector>
#include <vtkParametricSpline.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkKochanekSpline.h>

class Spline: public vtkParametricSpline{
public:
    Spline(vtkSmartPointer<vtkPoints> points = nullptr);
    ~Spline() override;

    void generateSpline();
    void updateSpline();
    void clearSpline();
    void closeSpline();
    vtkSmartPointer<vtkPoints> getPoints() const { return points; }
    void setNewPoints(const vtkSmartPointer<vtkPoints>& newPoints) { points = newPoints; }
    void setGeneralOffset(const std::vector<double>& newOffset) { generalOffset = newOffset; }
    std::vector<double> getGeneralOffset() const { return generalOffset; }
    void addExtraPointsForSnap(vtkPolyData* polyData);

private:
    vtkSmartPointer<vtkPoints> points;
    std::vector<double> generalOffset = {0.0,0.0,0.0};
    vtkSmartPointer<vtkKochanekSpline> xSpline;
    vtkSmartPointer<vtkKochanekSpline> ySpline;
    vtkSmartPointer<vtkKochanekSpline> zSpline;
};