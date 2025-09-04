#include <QString>
#include <QFile>
#include <QTextStream>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <QWidget>

class FileManager {
public:
    FileManager(const QString &filePath);
    bool readFile(QString &content);
    bool writeFile(const QString &content);

    // Opens a dialog and loads a PLY file as vtkPolyData
    static vtkSmartPointer<vtkPolyData> openPLYDialog(QWidget* parent = nullptr);

private:
    QString filePath;
};
