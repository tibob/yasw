#ifndef BASEFILTER_H
#define BASEFILTER_H

#include <QPixmap>
#include <QWidget>
#include <QObject>
#include "basefilterwidget.h"


class BaseFilter : public QObject
{
    Q_OBJECT
public:
    BaseFilter(QObject * parent = 0);
    ~BaseFilter();
    void setImage(const QPixmap pixmap);
    virtual QPixmap getFilteredImage();

    AbstractFilterWidget* getWidget();
    QString getName();
    /* For later use :
       setSettings()
       getSettings()
       */
public slots:
    virtual void recalculate();

protected:
    QPixmap inputPixmap;
    QPixmap outputPixmap;
    AbstractFilterWidget *filterWidget;
private:
    BaseFilterWidget* widget;

};

#endif // BASEFILTER_H
