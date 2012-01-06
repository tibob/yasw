#ifndef DEKEYSTONING_H
#define DEKEYSTONING_H

#include "basefilter.h"
#include "dekeystoningwidget.h"

class Dekeystoning : public BaseFilter
{
    Q_OBJECT
public:
    Dekeystoning();
    AbstractFilterWidget* getWidget();
    QString getName();
private:
    DekeystoningWidget *widget;
public slots:
    virtual void recalculate();
};

#endif // DEKEYSTONING_H
