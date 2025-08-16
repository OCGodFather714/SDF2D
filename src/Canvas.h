#pragma once

#include <QOpenGLWidget>
#include <QImage>
#include <QPoint>
#include <vector>

struct Frame {
    QImage image;
};

class Canvas : public QOpenGLWidget {
    Q_OBJECT
public:
    explicit Canvas(QWidget* parent = nullptr);
    void newScene();
    void importImage(const QString& path);
    void exportPngSequence(const QString& dir);

public slots:
    void setOnionPrev(bool on) { onionPrev = on; update(); }
    void setOnionNext(bool on) { onionNext = on; update(); }
    void setFps(int v) { fps = v; }

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

public:
    std::vector<Frame> frames;
    int current = 0;

private:
    bool drawing = false;
    QPoint last;
    bool onionPrev = false, onionNext = false;
    int fps = 24;
};
