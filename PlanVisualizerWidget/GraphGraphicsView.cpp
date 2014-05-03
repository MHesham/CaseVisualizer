#include "stdafx.h"
#include "IStrategizerEx.h"
#include "GraphGraphicsView.h"
#include <QGLWidget>

using namespace IStrategizer;
using namespace std;

GraphGraphicsView::GraphGraphicsView()
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    this->setRenderHints(QPainter::Antialiasing);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}
//----------------------------------------------------------------------------------------------
void GraphGraphicsView::wheelEvent(QWheelEvent* p_wheelEvent)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double correctScaleFactor = p_wheelEvent->delta() > 0 ? 1.15 : 0.85;
    this->scale(correctScaleFactor, correctScaleFactor);
}