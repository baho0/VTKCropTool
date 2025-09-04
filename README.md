# VTK Spline Crop Tool

A sophisticated 3D mesh processing application built with Qt5 and VTK that enables interactive spline-based cropping of 3D objects. This tool allows users to define custom cutting paths using spline curves with precise marker placement and snap-to-surface functionality.

## Features

### 🎯 Interactive Spline Drawing
- **Marker-based spline creation**: Click on 3D objects to place control points (markers)
- **Real-time spline visualization**: See spline curves update dynamically as you add markers
- **Snap-to-surface functionality**: Automatically snap markers to the surface of 3D objects for precise placement

### ✂️ Advanced Cropping System
- **Spline-based cutting**: Use custom drawn splines as cutting paths to crop 3D objects
- **Tube filter implementation**: Converts splines to 3D volumes for accurate mesh clipping
- **Region extraction**: Automatically select the desired region after cropping operation

### 🎮 Interactive Manipulation
- **Drag-and-drop markers**: Seamlessly move placed markers by dragging them across the surface
- **Real-time updates**: Splines update instantly as markers are repositioned
- **Surface snapping**: Markers automatically snap to the nearest surface point during movement

### 🎨 Professional Visualization
- **Smooth rendering**: Phong shading with proper normal computation for realistic visualization
- **Ambient lighting**: Carefully tuned lighting system for optimal 3D object perception
- **Dark theme interface**: Modern UI with professional dark blue background

## Technical Architecture

### Core Components
- **VTKWidget**: Central 3D rendering component with VTK integration
- **SplineCropTool**: Implements the core spline-to-mesh cropping algorithm
- **VtkMarkerHandler**: Manages interactive 3D markers and their visualization
- **VtkSplineHandler**: Handles spline curve generation and rendering
- **VtkSnapDragInteractor**: Custom VTK interactor for surface-snapped dragging

### Key Technologies
- **VTK 9.1**: Advanced 3D visualization and mesh processing
- **Qt5**: Modern cross-platform GUI framework
- **OpenGL**: Hardware-accelerated 3D rendering
- **PLY Format**: Standard 3D mesh file format support

## Installation & Build

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install qtbase5-dev libvtk9-qt-dev cmake build-essential

# Or ensure you have:
- Qt5 (qtbase5-dev)
- VTK 9.1 with Qt support (libvtk9-qt-dev)
- CMake >= 3.12
- C++17 compatible compiler (GCC 9+)
```

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/baho0/VTKCropTool.git
cd VtkCropTool

# Create and enter build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the application
make -j$(nproc)

# Run the application
./VTKCropTool
```

## Usage Guide

### 1. Loading 3D Objects
1. Launch the application
2. Click the **File** menu in the toolbar
3. Select **Open** and choose a PLY file
4. The 3D object will be loaded and displayed with smooth shading

### 2. Creating Spline Cutting Paths
1. Click **Activate Crop** in the toolbox to enable marker placement mode
2. Click on the 3D object surface to place control points (red spherical markers)
3. Continue clicking to add more points - a spline curve will automatically form
4. Place at least 4 markers for optimal spline generation

### 3. Precise Marker Positioning
1. After placing initial markers, click **Snap** to enable surface snapping mode
2. Additional interpolated points will be added to the spline for smoother curves
3. Drag any marker to reposition it - it will automatically snap to the surface
4. The spline updates in real-time as you move markers

### 4. Executing the Crop Operation
1. Once satisfied with your spline placement, click **Apply Crop**
2. The application will:
   - Convert the spline to a 3D tube volume
   - Use it as a clipping function to cut the mesh
   - Extract and display the desired region
3. The result shows the cropped portion of the original object

### 5. Resetting and Starting Over
- Click **Reset** to clear all markers and splines
- Load a new object or start a new cutting operation

## Project Structure

```
VtkCropTool/
├── main.cpp                          # Application entry point
├── CMakeLists.txt                     # Build configuration
├── ui/                                # User Interface Components
│   ├── MainWindow.cpp/.h              # Main application window
│   ├── VTKWidget.cpp/.h               # Central 3D rendering widget
│   └── components/                    # UI components
│       ├── Toolbar.cpp/.h             # File operations toolbar
│       ├── Toolbox.cpp/.h             # Tool selection panel
│       └── tools/
│           └── CropTool.cpp/.h        # Crop tool UI controls
├── core/                              # Core Functionality
│   └── FileManager.cpp/.h             # PLY file loading and management
└── tools/                             # 3D Processing Tools
    ├── SplineCropTool.cpp/.h          # Core cropping algorithm
    ├── VtkMarkerHandler.cpp/.h        # Marker management system
    ├── VtkSplineHandler.cpp/.h        # Spline generation and rendering
    ├── VtkSnapDragInteractor.cpp/.h   # Surface-snapped interaction
    └── components/                    # Tool components
        ├── Marker.cpp/.h              # Individual marker implementation
        └── Spline.cpp/.h              # Spline curve implementation
```

## Key Algorithms

### Spline Generation
- Uses VTK's parametric spline functions to generate smooth curves through marker points
- Automatically handles curve interpolation and point distribution

### Surface Snapping
- Implements ray-casting from screen coordinates to 3D surface
- Uses VTK's cell picker for accurate surface point detection

### Mesh Cropping
- Converts spline curves to 3D tube geometry using VTK's tube filter
- Creates implicit distance functions for mesh clipping operations
- Extracts connected regions using VTK's connectivity filters

## Advanced Features

- **Real-time feedback**: All operations provide immediate visual feedback
- **Robust error handling**: Graceful handling of edge cases and invalid operations
- **Memory management**: Smart pointer usage for automatic memory management
- **Cross-platform compatibility**: Runs on Linux, Windows, and macOS

## Contributing

This project demonstrates advanced VTK and Qt integration techniques including:
- Custom VTK interactor styles
- Real-time 3D mesh manipulation
- Interactive spline curve editing
- Surface-constrained object movement
- Professional 3D visualization techniques

## Technical Notes

- Built with modern C++17 features
- Uses VTK's OpenGL2 rendering backend for optimal performance
- Implements custom interaction paradigms for intuitive 3D editing
- Demonstrates integration of complex VTK algorithms with Qt GUI systems

## Authors
- baho0

## Acknowledgements
- [Qt](https://www.qt.io/)
- [VTK](https://vtk.org/)
