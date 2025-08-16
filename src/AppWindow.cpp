#include "AppWindow.h"
#include "Canvas.h"
#include "DockLayers.h"
#include "DockTimeline.h"
#include "DockProperties.h"
#include "io/Sdf2dFile.h"

#include <QDockWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QKeySequence>

AppWindow::AppWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("SDF2D — Created by Stephen D. Farrar II");
    setMinimumSize(1200, 800);
    setupUi();
    setupMenus();
    statusBar()->showMessage("Ready");
}

void AppWindow::setupUi()
{
    canvas = new Canvas(this);
    setCentralWidget(canvas);

    auto d1 = new QDockWidget("Layers", this);
    layers = new DockLayers(d1);
    d1->setWidget(layers);
    addDockWidget(Qt::LeftDockWidgetArea, d1);

    auto d2 = new QDockWidget("Timeline", this);
    timeline = new DockTimeline(d2);
    d2->setWidget(timeline);
    addDockWidget(Qt::BottomDockWidgetArea, d2);

    auto d3 = new QDockWidget("Properties", this);
    props = new DockProperties(d3);
    d3->setWidget(props);
    addDockWidget(Qt::RightDockWidgetArea, d3);

    auto tb = addToolBar("Onion/FPS");
    auto prev = new QCheckBox("Prev");
    auto next = new QCheckBox("Next");
    auto fps  = new QSpinBox();
    fps->setRange(1, 240);
    fps->setValue(24);

    tb->addWidget(new QLabel("Onion: "));
    tb->addWidget(prev);
    tb->addWidget(next);
    tb->addSeparator();
    tb->addWidget(new QLabel("FPS"));
    tb->addWidget(fps);

    QObject::connect(prev, &QCheckBox::toggled, canvas, &Canvas::setOnionPrev);
    QObject::connect(next, &QCheckBox::toggled, canvas, &Canvas::setOnionNext);
    QObject::connect(fps,  &QSpinBox::valueChanged, canvas, &Canvas::setFps);
}

void AppWindow::setupMenus()
{
    auto file = menuBar()->addMenu("&File");
    file->addAction("&New",    this, &AppWindow::newScene, QKeySequence::New);
    file->addAction("&Open…",  this, &AppWindow::openScene, QKeySequence::Open);
    file->addAction("&Save",   this, &AppWindow::saveScene, QKeySequence::Save);
    file->addSeparator();
    file->addAction("Import &Image…", this, &AppWindow::importImage);
    file->addSeparator();
    file->addAction("Export &PNG Sequence…", this, &AppWindow::exportPngSequence);
    file->addSeparator();
    file->addAction("E&xit", this, &QWidget::close, QKeySequence::Quit);

    auto help = menuBar()->addMenu("&Help");
    help->addAction("About SDF2D", [this]{
        QMessageBox::about(this, "About SDF2D",
            "SDF2D — 2D Animation Starter\n"
            "Created by Stephen D. Farrar II\n\n"
            "Qt6 dockable UI, OpenGL canvas placeholder, simple I/O."
        );
    });
}

void AppWindow::newScene()
{
    canvas->newScene();
    statusBar()->showMessage("New scene", 1500);
}

void AppWindow::openScene()
{
    auto fn = QFileDialog::getOpenFileName(this, "Open .sdf2d or .json", {}, "SDF2D (*.sdf2d *.json)");
    if (fn.isEmpty()) return;
    if (!Sdf2dFile::load(fn, canvas))
        QMessageBox::warning(this, "Open Failed", "Could not open.");
}

void AppWindow::saveScene()
{
    auto fn = QFileDialog::getSaveFileName(this, "Save .sdf2d", "untitled.sdf2d", "SDF2D (*.sdf2d)");
    if (fn.isEmpty()) return;
    if (!Sdf2dFile::save(fn, canvas))
        QMessageBox::warning(this, "Save Failed", "Could not save.");
}

void AppWindow::importImage()
{
    auto fn = QFileDialog::getOpenFileName(this, "Import Image", {}, "Images (*.png *.jpg *.jpeg)");
    if (fn.isEmpty()) return;
    canvas->importImage(fn);
}

void AppWindow::exportPngSequence()
{
    auto dir = QFileDialog::getExistingDirectory(this, "Export PNG Sequence");
    if (dir.isEmpty()) return;
    canvas->exportPngSequence(dir);
}
