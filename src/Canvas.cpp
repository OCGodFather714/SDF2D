#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDir>
#include <QPen>
#include <QColor>

Canvas::Canvas(QWidget* parent)
    : QOpenGLWidget(parent)
{
    setAutoFillBackground(false);
    setMouseTracking(true);
    newScene();
}

void Canvas::newScene()
{
    frames.clear();
    Frame f;
    f.image = QImage(1280, 720, QImage::Format_RGBA8888);
    f.image.fill(QColor(18, 22, 28));
    frames.push_back(f);
    current = 0;
    update();
}

void Canvas::importImage(const QString& path)
{
    if (frames.empty()) newScene();
    QImage img(path);
    if (!img.isNull()) {
        QPainter painter(&frames[current].image);
        painter.drawImage(0, 0, img);
        painter.end();
        update();
    }
}

void Canvas::exportPngSequence(const QString& dir)
{
    QDir d(dir);
    int i = 0;
    for (const auto& f : frames) {
        QString name = QString("frame_%1.png").arg(i++, 4, 10, QChar('0'));
        f.image.save(d.filePath(name));
    }
}

void Canvas::initializeGL() {}
void Canvas::resizeGL(int, int) {}

void Canvas::paintGL()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw checkerboard background
    const int s = 16;
    for (int y = 0; y < height(); y += s)
        for (int x = 0; x < width(); x += s) {
            QColor a(30, 32, 40), b(36, 38, 46);
            painter.fillRect(QRect(x, y, s, s), ((x / s + y / s) % 2 == 0) ? a : b);
        }

    if (!frames.empty()) {
        const QImage& img = frames[current].image;
        QSizeF area = size();
        double scale = std::min(area.width() / img.width(), area.height() / img.height());
        QSizeF sz(img.width() * scale, img.height() * scale);
        QRectF tgt((area.width() - sz.width()) / 2, (area.height() - sz.height()) / 2, sz.width(), sz.height());

        if (onionPrev && current > 0) {
            painter.setOpacity(0.3);
            painter.drawImage(tgt, frames[current - 1].image);
            painter.setOpacity(1.0);
        }
        painter.drawImage(tgt, img);
        if (onionNext && current + 1 < static_cast<int>(frames.size())) {
            painter.setOpacity(0.3);
            painter.drawImage(tgt, frames[current + 1].image);
            painter.setOpacity(1.0);
        }
    }

    painter.setPen(QColor(255, 255, 255, 210));
    painter.drawText(10, 20, QString("Frame %1/%2  |  FPS %3").arg(current + 1).arg(frames.size()).arg(fps));
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        last = event->pos();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if (drawing && !frames.empty()) {
        QPainter painter(&frames[current].image);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPen pen(QColor(122, 92, 255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(last, event->pos());
        painter.end();
        last = event->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        drawing = false;
}
