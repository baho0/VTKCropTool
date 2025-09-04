#include "Toolbox.h"
#include <QVBoxLayout>
#include "tools/CropTool.h"

Toolbox::Toolbox(QWidget* parent)
    : QToolBox(parent)
{
    createActions();
    createUI();
    createConnections();
}

Toolbox::~Toolbox() {}

void Toolbox::createActions() {
    // Create actions for the toolbox
}

void Toolbox::createConnections() {
    // Create connections for the toolbox
}

void Toolbox::createUI() {
    // Generate Layout
    QWidget *toolboxWidget = new QWidget(this);
    QVBoxLayout *toolboxLayout = new QVBoxLayout(toolboxWidget);
    addItem(toolboxWidget, "Toolbox");

    // Create the UI elements for the toolbox
    this->cropTool = new CropTool(this);
    toolboxLayout->addWidget(cropTool);

    // Add stretch
    toolboxLayout->addStretch();
}
