#ifndef ROTATIONWIDGET_H
#define ROTATIONWIDGET_H

#include <QWidget>
#include "abstractfilterwidget.h"

namespace Ui {
    class RotationWidget;
}

class RotationWidget : public AbstractFilterWidget
{
    Q_OBJECT

public:
    explicit RotationWidget(QWidget *parent = 0);
    ~RotationWidget();
    void setPixmap(QPixmap pixmap);
    void setPreview(QPixmap pixmap);
    bool preview();
    int rotation();

private slots:
    void on_rotateLeft_clicked();
    void on_rotateRight_clicked();
    void on_preview_toggled(bool checked);

signals:
    void rotationChanged();

private:
    Ui::RotationWidget *ui;
    int rotationAngle;
};

#endif // ROTATIONWIDGET_H
