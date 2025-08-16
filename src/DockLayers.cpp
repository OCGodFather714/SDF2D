#include "DockLayers.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

DockLayers::DockLayers(QWidget* p): QWidget(p){
  auto *l=new QVBoxLayout(this);
  l->addWidget(new QLabel("Layers (placeholder)"));
  l->addWidget(new QPushButton("Add Raster Layer"));
  l->addStretch(1);
}
