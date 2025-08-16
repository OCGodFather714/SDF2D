#include "DockProperties.h"
#include <QVBoxLayout>
#include <QLabel>

DockProperties::DockProperties(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Properties (placeholder)"));
    layout->addStretch(1);
}
