#ifndef FILTERCONTAINER_H
#define FILTERCONTAINER_H

#include <QTabWidget>
#include <QMap>
#include "basefilter.h"
#include "dekeystoning.h"
#include "abstractfilterwidget.h"

class FilterContainer : public QTabWidget
{
    Q_OBJECT
public:
    FilterContainer(QWidget * parent = 0);
    ~FilterContainer();
    void setImage(QPixmap pixmap);
public slots:
    void tabChanged(int index);
private:
    BaseFilter *baseFilter;
    Dekeystoning *dekeystoningFilter;
    QList<BaseFilter *> tabToFilter;
    int oldIndex; //stores the last selected index

    void updateCurrentTabPixmap(int fromIndex = 1);
};

#endif // FILTERCONTAINER_H
