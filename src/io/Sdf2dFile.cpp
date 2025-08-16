#include "Sdf2dFile.h"
#include "../Canvas.h"
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QStringList>

bool Sdf2dFile::save(const QString& path, Canvas* c)
{
    QFileInfo info(path);
    QDir dir;
    dir.mkpath(info.absolutePath());

    QDir out(path);
    if (!out.exists()) QDir().mkpath(out.absolutePath());

    QDir assets(out.filePath("assets"));
    QDir().mkpath(assets.absolutePath());

    for (int i = 0; i < static_cast<int>(c->frames.size()); ++i) {
        c->frames[i].image.save(assets.filePath(QString("frame_%1.png").arg(i, 4, 10, QChar('0'))));
    }

    QFile scene(out.filePath("scene.json"));
    if (scene.open(QIODevice::WriteOnly)) {
        scene.write("{\"format\":\"sdf2d-0.1\",\"created_by\":\"Stephen D. Farrar II\"}");
        scene.close();
    }
    return true;
}

bool Sdf2dFile::load(const QString& path, Canvas* c)
{
    QDir assets(QFileInfo(path).filePath() + "/assets");
    if (!assets.exists()) return false;
    c->frames.clear();

    QStringList files = assets.entryList(QStringList() << "frame_*.png", QDir::Files, QDir::Name);
    if (files.isEmpty()) return false;

    for (const auto& f : files) {
        Frame fr;
        fr.image = QImage(assets.filePath(f));
        c->frames.push_back(fr);
    }

    c->current = 0;
    c->update();
    return true;
}
