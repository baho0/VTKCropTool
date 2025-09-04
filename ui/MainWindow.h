#pragma once
#include <QMainWindow>
#include <QLayout>
#include <QWidget>
#include "VTKWidget.h"
#include "components/Toolbox.h"
#include "components/Toolbar.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onFileOpenRequested();
private:
    VTKWidget* vtkWidget;
    QWidget* centralWidget;
    QLayout* mainLayout;
    Toolbox* toolbox;
    Toolbar* toolbar;
    void setupConnections();
    void toggleMarker();
    void resetMarker();
    void applyCrop();
    void snapSpline();
};
