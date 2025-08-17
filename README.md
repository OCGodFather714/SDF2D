# SDF2D — 2D Animation Starter

Desktop Qt app + static website. The app provides a dockable UI and a simple canvas (draw lines, onion-skin preview, import image, export PNG sequence).  
The website is a landing page with features and a “Download” button.

Created by Stephen D. Farrar II.

---

## Features (Starter)
- Qt 6 dockable UI: Layers, Timeline, Properties panes.
- Canvas: simple drawing with mouse, onion-skin prev/next toggles, FPS indicator.
- Import image (PNG/JPG), export PNG sequence.
- Minimal `.sdf2d` folder format: `scene.json` + `assets/frame_XXXX.png`.
- Static site in `site/` to host downloads and docs.

> Roadmap (not in this starter): Skia GPU canvas, vector+raster tools, auto-inbetween, basic rigging, effects, camera, on-device ML helpers.

---

## Repo Structure.
├─ CMakeLists.txt
├─ site/
│  ├─ index.html
│  ├─ styles.css
│  └─ assets/
│     ├─ logo.svg
│     └─ hero.svg
└─ src/
├─ main.cpp
├─ AppWindow.{h,cpp}
├─ Canvas.{h,cpp}
├─ DockLayers.{h,cpp}
├─ DockTimeline.{h,cpp}
├─ DockProperties.{h,cpp}
├─ Document.{h,cpp}
├─ io/Sdf2dFile.{h,cpp}
└─ ml/MLService.{h,cpp}---

## Prerequisites
- CMake 3.21+
- Qt 6.4+ (Widgets, OpenGLWidgets)
- C++20 compiler

### macOS
- Xcode Command Line Tools  
- Homebrew for CMake and Qt

### Windows
- Visual Studio 2022 (Desktop C++), CMake, Qt 6 (MSVC)

### Linux (Debian/Ubuntu)
- `build-essential`, `cmake`, `qt6-base-dev`, `libqt6opengl6-dev`

---

## Build & Run

### macOS
```bash
xcode-select --install
brew install cmake qt
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
cmake --build build -j
open build/SDF2D.app
# or: ./build/SDF2D.app/Contents/MacOS/SDF2D
```
### Windows
```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="C:\Qt\6.x.x\msvc2019_64"
cmake --build build --config Release
.\build\Release\SDF2D.exe
```
### Linux (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install -y build-essential cmake qt6-base-dev libqt6opengl6-dev
cmake -S . -B build
cmake --build build -j
./build/SDF2D
```

---

## Quick Start (App)
  1. File → New to clear the canvas.
  2. Draw with the left mouse button.
  3. Toggle onion skin in the toolbar (Prev/Next).
  4. File → Import Image to place a PNG/JPG on the frame.
  5. File → Export PNG Sequence to write frame_0000.png, frame_0001.png, …

---

## Website

### Local Preview
```bash
cd site
python3 -m http.server 5173
# open http://localhost:5173
```
### Publish with GitHub Pages
- GitHub → Settings → Pages → “Deploy from a branch”
- Branch: main
- Folder: /site
- Save. Your site will be at:
  https://<your-username>.github.io/<repo-name>/

To change the download button, edit site/index.html and point it to a GitHub Release asset or any hosted file.

⸻

## Configuration Notes

- Because src/io/Sdf2dFile.cpp sits under src/io/, its include path to the canvas is:
  ```cpp
  #include "../Canvas.h"
  ```
- If CMake cannot find Qt on macOS, configure with:
  ```bash
  cmake -S . -B build \
    -DQt6_DIR="$(brew --prefix qt)/lib/cmake/Qt6" \
    -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
  ```

---

## Troubleshooting

- **Could NOT find Qt6**  
  Ensure Qt is installed and pass -DCMAKE_PREFIX_PATH as above.

- **macOS “cocoa platform plugin” error**  
  Launch the bundle: open build/SDF2D.app.

- **Weird build state**  
  Reconfigure:
  ```bash
  rm -rf build
  cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
  cmake --build build -j
  ```

---

## License and Third-Party

- Qt is available under LGPL/commercial licenses. For LGPL, dynamically link Qt when distributing binaries and provide license texts.
- Planned future libs (Skia, ONNX Runtime) are permissive; include their NOTICE files when added.

⸻

## Credits

SDF2D — Created by Stephen D. Farrar II.
