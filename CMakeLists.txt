cmake_minimum_required(VERSION 3.21)
project(SDF2D LANGUAGES CXX)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 6
find_package(Qt6 6.4 COMPONENTS Widgets OpenGLWidgets REQUIRED)
qt_standard_project_setup()   # enables AUTOMOC/AUTOUIC/AUTORCC

# Sources/headers (paths match your repo: src/, src/io, src/ml)
set(SOURCES
  src/main.cpp
  src/AppWindow.cpp
  src/Canvas.cpp
  src/DockLayers.cpp
  src/DockTimeline.cpp
  src/DockProperties.cpp
  src/Document.cpp
  src/io/Sdf2dFile.cpp
  src/ml/MLService.cpp
)
set(HEADERS
  src/AppWindow.h
  src/Canvas.h
  src/DockLayers.h
  src/DockTimeline.h
  src/DockProperties.h
  src/Document.h
  src/io/Sdf2dFile.h
  src/ml/MLService.h
)

qt_add_executable(SDF2D ${SOURCES} ${HEADERS})
target_include_directories(SDF2D PRIVATE src)
target_link_libraries(SDF2D PRIVATE Qt6::Widgets Qt6::OpenGLWidgets)
