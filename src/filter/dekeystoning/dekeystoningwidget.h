#ifndef DEKEYSTONINGWIDGET_H
#define DEKEYSTONINGWIDGET_H

#include <QWidget>
#include "abstractfilterwidget.h"

namespace Ui {
    class DekeystoningWidget;
}

class DekeystoningWidget : public AbstractFilterWidget {
    Q_OBJECT
public:
    DekeystoningWidget(QWidget *parent = 0);
    ~DekeystoningWidget();
    void setPixmap(QPixmap pixmap);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DekeystoningWidget *ui;
};

#endif // DEKEYSTONINGWIDGET_H
