#include "Toolbar.h"
#include <QToolBar>
#include <QAction>

Toolbar::Toolbar(QWidget *parent)
    : QToolBar(parent)
{
    setWindowTitle("Toolbar");
    setMovable(true);


    QAction *fileAction = new QAction("File", this);
    QAction *editAction = new QAction("Edit", this);
    addAction(fileAction);
    addSeparator();
    addAction(editAction);

    connect(fileAction, &QAction::triggered, this, &Toolbar::fileOpenRequested);
    fileAction->setShortcut(QKeySequence::Open);
}
