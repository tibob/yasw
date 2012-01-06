#include "dekeystoning.h"

Dekeystoning::Dekeystoning()
{
    widget = new DekeystoningWidget();
    filterWidget = widget;
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

}

