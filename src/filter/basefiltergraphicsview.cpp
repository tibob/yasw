#include "basefiltergraphicsview.h"
#include <QWheelEvent>
#include <math.h>
#include <QDebug>
#include <QTransform>


BaseFilterGraphicsView::BaseFilterGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
//    scene->setSceneRect(0, 0, 110, 110);
    setScene(scene);

    pixmapItem = new QGraphicsPixmapItem();
    scene->addItem(pixmapItem);
}

void
BaseFilterGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;
        double factor = pow(1.125, numSteps);
        scale(factor, factor);
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void BaseFilterGraphicsView::setPixmap(const QPixmap pixmap)
{
    scene->setSceneRect(pixmap.rect());
    pixmapItem->setPixmap(pixmap);

    /* Zoom the QGraphicsView to fit the new Pixmap */
//todo does not work for hidden QGraphicsView -> set zoomfactor ?
    fitInView(pixmapItem, Qt::KeepAspectRatio);
}
