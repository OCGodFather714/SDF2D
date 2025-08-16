cmake_minimum_required(VERSION 3.21)
project(SDF2D LANGUAGES CXX)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic Qt handling
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find required Qt6 components
find_package(Qt6 6.4 COMPONENTS Widgets OpenGLWidgets REQUIRED)

# Source and header files
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

qt_standard_project_setup()

qt_add_executable(SDF2D
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(SDF2D PRIVATE src)
target_link_libraries(SDF2D PRIVATE Qt6::Widgets Qt6::OpenGLWidgets)

# macOS: Set rpath so the app finds Homebrew Qt at runtime
if(APPLE)
    set_target_properties(SDF2D PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks;@loader_path/../Frameworks;${Qt6_DIR}/../lib"
        BUILD_WITH_INSTALL_RPATH ON
    )
endif()

# Optional: Install target for easy packaging
install(TARGETS SDF2D)
