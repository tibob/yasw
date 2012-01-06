#include "dekeystoning.h"
#include <QDebug>

Dekeystoning::Dekeystoning()
{
    widget = new DekeystoningWidget();
    filterWidget = widget;
    connect(widget, SIGNAL(polygonChanged()), this, SLOT(recalculate()));
}

/*! \brief Retruns the name of the filter */
QString Dekeystoning::getName()
{
    return QString("Dekeystoning");
}

/*! \todo cannot this be handled by BaseFilter::getWidget() ? */
AbstractFilterWidget* Dekeystoning::getWidget()
{
    return widget;
}

void Dekeystoning::recalculate()
{
    qDebug() << "recalculate()";

    QPolygonF polygon = widget->polygon();

    QTransform transformMatrix;
    /* it might not be possbible to calculate a treansformation matrix */
    if (!QTransform::quadToSquare(polygon, transformMatrix)) {
        qDebug() << "No transformation exists for this";
        return;
    }

    qreal width  = widget->meanWidth();
    qreal height = widget->meanHeight();
    QTransform scaleMatrix = QTransform::fromScale(width, height);

    QTransform transformationMatrix = transformMatrix * scaleMatrix;

    outputPixmap = inputPixmap.transformed(transformationMatrix);

    widget->setPreview(outputPixmap);
}

