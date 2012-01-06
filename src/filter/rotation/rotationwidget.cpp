#include "rotationwidget.h"
#include "ui_rotationwidget.h"
#include <QDebug>

RotationWidget::RotationWidget(QWidget *parent) :
    AbstractFilterWidget(parent),
    ui(new Ui::RotationWidget)
{
    ui->setupUi(this);
    rotationAngle = 0;
}

RotationWidget::~RotationWidget()
{
    delete ui;
}

void RotationWidget::setPixmap(QPixmap pixmap)
{
    inputPixmap = pixmap;
    if (!preview())
        ui->view->setPixmap(pixmap);
}

void RotationWidget::setPreview(QPixmap pixmap)
{
    previewPixmap = pixmap;
    if (preview())
        ui->view->setPixmap(pixmap);
}


void RotationWidget::on_rotateLeft_clicked()
{
    rotationAngle = (rotationAngle - 90) % 360;
    qDebug() << rotationAngle;
    emit rotationChanged();
}

void RotationWidget::on_rotateRight_clicked()
{
    rotationAngle = (rotationAngle + 90) % 360;;
    qDebug() << rotationAngle;
    emit rotationChanged();
}


void RotationWidget::on_preview_toggled(bool checked)
{
    if (checked)
        ui->view->setPixmap(previewPixmap);
    else
        ui->view->setPixmap(inputPixmap);
}

bool RotationWidget::preview()
{
    return ui->preview->isChecked();
}

int RotationWidget::rotation()
{
    return rotationAngle;
}

