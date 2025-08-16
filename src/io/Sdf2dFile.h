#pragma once

#include <QString>

class Canvas;

namespace Sdf2dFile {
    bool save(const QString& path, Canvas* canvas);
    bool load(const QString& path, Canvas* canvas);
}
