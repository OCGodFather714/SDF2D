#include "Document.h"

QJsonObject Document::toJson() const
{
    QJsonObject j;
    j["width"] = width;
    j["height"] = height;
    j["fps"] = fps;
    return j;
}

Document Document::fromJson(const QJsonObject& j)
{
    Document d;
    d.width = j["width"].toInt(1920);
    d.height = j["height"].toInt(1080);
    d.fps = j["fps"].toInt(24);
    return d;
}
