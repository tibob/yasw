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
    void setPreview(QPixmap pixmap);
    bool preview();
    qreal meanWidth();
    qreal meanHeight();
    QPolygonF polygon();
    bool polygonMoved();
    void resetPolygonMoved();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DekeystoningWidget *ui;

private slots:
    void on_preview_toggled(bool checked);

signals:
    void polygonChanged();
};

#endif // DEKEYSTONINGWIDGET_H
