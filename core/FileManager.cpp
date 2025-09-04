#include "FileManager.h"
#include <QFileDialog>
#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>
#include <vtkPolyData.h>

FileManager::FileManager(const QString &filePath)
    : filePath(filePath) {}

bool FileManager::readFile(QString &content) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);
    content = in.readAll();
    return true;
}

bool FileManager::writeFile(const QString &content) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);
    out << content;
    return true;
}

vtkSmartPointer<vtkPolyData> FileManager::openPLYDialog(QWidget* parent) {
    QString filename = QFileDialog::getOpenFileName(parent, "Open PLY File", "", "PLY Files (*.ply)");
    if (filename.isEmpty())
        return nullptr;
    auto reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName(filename.toStdString().c_str());
    reader->Update();
    return reader->GetOutput();
}
