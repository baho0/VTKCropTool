#include "MainWindow.h"
#include "VTKWidget.h"
#include "components/Toolbar.h"
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include "../core/FileManager.h"
#include "components/Toolbox.h"
#include <iostream>
#include <QDebug>
#include "components/tools/CropTool.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Spline Crop Tool With VTK");
    resize(1600, 1200);

    //init QDebug
    qDebug() << "MainWindow initialized";

    //Create and set central widget
    this->mainLayout = new QVBoxLayout();
    this->centralWidget = new QWidget(this);
    this->centralWidget->setLayout(this->mainLayout);
    setCentralWidget(this->centralWidget);
    
    //Add toolbar
    this->toolbar = new Toolbar(this);
    addToolBar(Qt::TopToolBarArea, this->toolbar);

    connect(this->toolbar, &Toolbar::fileOpenRequested, this, &MainWindow::onFileOpenRequested);

    //HBoxLayout for VTK and Toolbox
    QWidget *windowContainer = new QWidget(this);
    QHBoxLayout *hLayout = new QHBoxLayout();
    windowContainer->setLayout(hLayout);
    mainLayout->addWidget(windowContainer);

    //Add VTK widget
    vtkWidget = new VTKWidget(this);
    hLayout->addWidget(vtkWidget);

    //Add Toolbox
    this->toolbox = new Toolbox(this);
    toolbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbox->setFixedWidth(200);
    hLayout->addWidget(toolbox);

    //setup connections
    setupConnections();

}

MainWindow::~MainWindow() {}

// Slot to handle file open
void MainWindow::onFileOpenRequested() {
    vtkSmartPointer<vtkPolyData> polyData = FileManager::openPLYDialog(this);
    if (polyData) {
        vtkWidget->setPolyDataFromFileManager(polyData);
    }
}

void MainWindow::setupConnections() {
    connect(this->toolbox->getCropTool(), &CropTool::activateCropRequested, this, &MainWindow::toggleMarker);
    connect(this->toolbox->getCropTool(), &CropTool::resetCropRequested, this, &MainWindow::resetMarker);
    connect(this->toolbox->getCropTool(), &CropTool::applyCropRequested, this, &MainWindow::applyCrop);
    connect(this->toolbox->getCropTool(), &CropTool::snapRequested, this, &MainWindow::snapSpline);
}

void MainWindow::toggleMarker() {
    if (vtkWidget) {
        vtkWidget->setIsMarkerEnabled(!vtkWidget->getIsMarkerEnabled());
        vtkWidget->setSplineDrawingForCropEnabled(vtkWidget->getIsMarkerEnabled());
        qDebug() << "Marker Enabled: " << vtkWidget->getIsMarkerEnabled();
    } else {
        qDebug() << "vtkWidget is nullptr!";
    }
}

void MainWindow::resetMarker() {
    if (vtkWidget) {
        vtkWidget->toggleResetCropMarker();
        qDebug() << "Marker Reset";
    } else {
        qDebug() << "vtkWidget is nullptr!";
    }
}

void MainWindow::applyCrop() {
    if (vtkWidget) {
        vtkWidget->toggleApplySplineCrop();
        qDebug() << "Apply Crop";
    } else {
        qDebug() << "vtkWidget is nullptr!";
    }
}

void MainWindow::snapSpline() {
    if (vtkWidget) {
        vtkWidget->toggleSnapMode();
        qDebug() << "Snap Spline";
    } else {
        qDebug() << "vtkWidget is nullptr!";
    }
}