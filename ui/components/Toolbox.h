#pragma once
#include <QToolBox>
#include "tools/CropTool.h"

class Toolbox : public QToolBox {
    Q_OBJECT
public:
    Toolbox(QWidget* parent = nullptr);
    ~Toolbox();
    CropTool* getCropTool() const { return cropTool; }
private:
    void createActions();
    void createConnections();
    void createUI();
    CropTool* cropTool;
};
