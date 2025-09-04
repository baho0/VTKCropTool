cmake_minimum_required(VERSION 3.12)
project(VTKCropTool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/vtk-9.1" "/usr/lib/x86_64-linux-gnu/qt5" "/usr/include/x86_64-linux-gnu/qt5" "/usr/include/vtk-9.1")


find_package(VTK REQUIRED COMPONENTS
    CommonCore
    CommonDataModel
    FiltersCore
    FiltersSources
    InteractionStyle
    RenderingCore
    RenderingOpenGL2
    GUISupportQt
    RenderingQt
    IOPLY
    CommonComputationalGeometry
)



find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(${VTK_USE_FILE})

set(CMAKE_AUTOMOC ON)

add_executable(VTKCropTool
    main.cpp
    ui/MainWindow.cpp
    ui/VTKWidget.cpp
    ui/components/Toolbar.cpp
    core/FileManager.cpp
    ui/components/Toolbox.cpp
    ui/components/tools/CropTool.cpp
    tools/VtkMarkerHandler.cpp
    tools/components/Marker.cpp
    tools/VtkSplineHandler.cpp
    tools/components/Spline.cpp
    tools/SplineCropTool.cpp
    tools/VtkSnapDragInteractor.cpp
)

target_link_libraries(VTKCropTool ${VTK_LIBRARIES} Qt5::Widgets)
