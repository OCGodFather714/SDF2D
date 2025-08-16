#pragma once

#include <QMainWindow>

class Canvas;
class DockLayers;
class DockTimeline;
class DockProperties;

class AppWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit AppWindow(QWidget* parent = nullptr);

private slots:
    void newScene();
    void openScene();
    void saveScene();
    void importImage();
    void exportPngSequence();

private:
    void setupUi();
    void setupMenus();

    Canvas* canvas = nullptr;
    DockLayers* layers = nullptr;
    DockTimeline* timeline = nullptr;
    DockProperties* props = nullptr;
};
