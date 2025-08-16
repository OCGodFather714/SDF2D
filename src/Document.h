#pragma once

#include <QJsonObject>

struct Document {
    int width = 1920;
    int height = 1080;
    int fps = 24;

    QJsonObject toJson() const;
    static Document fromJson(const QJsonObject&);
};
