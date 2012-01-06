#include "basefilter.h"

/*! \class BaseFilter

  \brief The BaseFilter class is the model for all Filter applied on pages.

  It should be inherited by every Filter. The PageFilter class is functional but does nothing, and
  returns the pixmap unmodified.

  Some functions are definied as virtual in order to allow the calling class use a unique interface
  (all Filter can be stored as a "BaseFilter" Class).
*/

/*! \brief  Constructs a Filter
*/
BaseFilter::BaseFilter(QObject * parent) : QObject(parent)
{
    widget = new BaseFilterWidget();
    filterWidget = widget;
}

BaseFilter::~BaseFilter()
{
    delete widget;
}


/*! \brief Set input Page

  This function is called by the calling class to set the Pixmap to be "filtered".
*/
void BaseFilter::setImage(QPixmap pixmap)
{
    inputPixmap = pixmap;
    filterWidget->setPixmap(pixmap);
    recalculate();
}

/*! \brief Returns the transformed page

  @returns The transformed page, or a null Pixmap if no page is available
*/
QPixmap BaseFilter::getFilteredImage()
{
    return outputPixmap;
}

/*! \brief Gets the widget to display the filter

    The returned widget must not be freed, it is handled by the class destructor.
    @returns The Widget for this Filter.
  */
AbstractFilterWidget* BaseFilter::getWidget()
{
    return widget;
}

/*! \brief Retruns the name of the filter */
QString BaseFilter::getName()
{
    return QString("Base Filer");
}

/*! \brief Recalculate the output Pixmap

    In the case of BaseFilter: does nothing as the filter does nothing.
*/
void BaseFilter::recalculate()
{
    outputPixmap = inputPixmap;
}





