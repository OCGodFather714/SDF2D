#pragma once

#include <QObject>

class MLService : public QObject {
    Q_OBJECT
public:
    explicit MLService(QObject* parent = nullptr)
        : QObject(parent) {}

    void smartInbetween() {}
    void cleanupAssist() {}
    void autoLipSync() {}
};
