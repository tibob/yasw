#ifndef ROTATION_H
#define ROTATION_H

#include <QObject>
#include <QWidget>
#include "rotationwidget.h"
#include "basefilter.h"

class Rotation: public BaseFilter
{
    Q_OBJECT
public:
    Rotation(QObject * parent = 0);
    AbstractFilterWidget* getWidget();
    QString getName();
public slots:
    void recalculate();

private:
    RotationWidget *widget;
    QTransform rotationMatrix;
};

#endif // ROTATION_H
