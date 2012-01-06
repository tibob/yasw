#include "rotation.h"

Rotation::Rotation(QObject * parent) : BaseFilter(parent)
{
    widget = new RotationWidget();
    filterWidget = widget;
    connect(widget, SIGNAL(rotationChanged()), this, SLOT(recalculate()));
}

QString Rotation::getName()
{
    return QString("Rotation");
}

AbstractFilterWidget * Rotation::getWidget()
{
    return widget;
}

void Rotation::recalculate()
{
    rotationMatrix.reset();
    rotationMatrix.rotate(widget->rotation());
    outputPixmap = inputPixmap.transformed(rotationMatrix);
    widget->setPreview(outputPixmap);
}

///*! \fixme implement this */
//QPixmap Rotation::getFilteredImage()
//{
//    return inputPixmap;
//}
