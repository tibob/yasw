#include "abstractfilterwidget.h"

/** \class FilterWidget
  \brief An abstract class for all Filter Widgets.

  \todo The class ist not abstract anymore...

  This abstract class describes the members a Filter Widget must have.
  It has to be inherited by all Filter Widgets.
*/

AbstractFilterWidget::AbstractFilterWidget(QWidget *parent) :
    QWidget(parent)
{
}

/** \brief Sets the input pixmap
  */
void AbstractFilterWidget::setPixmap(QPixmap pixmap)
{
    inputPixmap = pixmap;
}

/** \brief Sets the filtered pixmap for preview */
void AbstractFilterWidget::setPreview(QPixmap pixmap)
{
    previewPixmap = pixmap;
}
