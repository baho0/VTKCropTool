#include "CropTool.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>

CropTool::CropTool(QWidget* parent)
    : QWidget(parent)
{
    createUI();
    createConnections();
}

CropTool::~CropTool() {}

void CropTool::createUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Crop Tool", this);
    layout->addWidget(title);

    activateCropButton = new QPushButton("Activate Crop", this);
    layout->addWidget(activateCropButton);

    QSlider* slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(0);
    slider->setMaximum(100);
    layout->addWidget(slider);

    applyCropButton = new QPushButton("Apply Crop", this);
    layout->addWidget(applyCropButton);

    snapButton = new QPushButton("Snap", this);
    layout->addWidget(snapButton);

    resetButton = new QPushButton("Reset", this);
    layout->addWidget(resetButton);

    setLayout(layout);
}

void CropTool::createConnections() {
    connect(activateCropButton, &QPushButton::clicked, this, [this]() {
        emit activateCropRequested();
    });
    connect(resetButton, &QPushButton::clicked, this, [this](){
        emit resetCropRequested();
    });
    connect(applyCropButton, &QPushButton::clicked, this, [this](){
        emit applyCropRequested();
    });
    connect(snapButton, &QPushButton::clicked, this, [this](){
        emit snapRequested();
    });
}
