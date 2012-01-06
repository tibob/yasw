#ifndef ABSTRACTFILTERWIDGET_H
#define ABSTRACTFILTERWIDGET_H

#include <QWidget>

class AbstractFilterWidget : public QWidget
{
public:
    AbstractFilterWidget(QWidget *parent = 0);
    //! \brief Sets the input pixmap
    virtual void setPixmap(QPixmap pixmap);
    //! \brief Sets the filtered pixmap for preview */
    virtual void setPreview(QPixmap pixmap);
protected:
    QPixmap inputPixmap;
    QPixmap previewPixmap;
};

#endif // ABSTRACTFILTERWIDGET_H
