#include "DockTimeline.h"
#include <QVBoxLayout>
#include <QLabel>

DockTimeline::DockTimeline(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Timeline / X-Sheet (placeholder)"));
    layout->addStretch(1);
}
