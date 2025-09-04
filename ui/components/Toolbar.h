#pragma once
#include <QToolBar>

class Toolbar : public QToolBar {
    Q_OBJECT
public:
    Toolbar(QWidget *parent = nullptr);

signals:
    void fileOpenRequested();
};
