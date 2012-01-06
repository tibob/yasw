#ifndef BASEFILTERWIDGET_H
#define BASEFILTERWIDGET_H

#include <QWidget>
#include "abstractfilterwidget.h"

namespace Ui {
    class BaseFilterWidget;
}

class BaseFilterWidget : public AbstractFilterWidget {
    Q_OBJECT
public:
    BaseFilterWidget(QWidget *parent = 0);
    ~BaseFilterWidget();
    void setPixmap(QPixmap pixmap);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::BaseFilterWidget *ui;
};

#endif // BASEFILTERWIDGET_H
