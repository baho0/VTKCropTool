#pragma once
#include <QWidget>
#include <QPushButton>

class CropTool : public QWidget {
    Q_OBJECT
public:
    CropTool(QWidget* parent = nullptr);
    ~CropTool();
    QPushButton* getActivateCropButton() const { return activateCropButton; }
    QPushButton* getApplyCropButton() const { return applyCropButton; }
    QPushButton* getResetButton() const { return resetButton; }
signals:
    void activateCropRequested();
    void resetCropRequested();
    void applyCropRequested();
    void snapRequested();
private:
    void createUI();
    void createConnections();
    void onActivateCrop();
    QPushButton* activateCropButton;
    QPushButton* applyCropButton;
    QPushButton* resetButton;
    QPushButton* snapButton;
};
