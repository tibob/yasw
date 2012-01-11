#include "croppingwidget.h"
#include "ui_croppingwidget.h"

CroppingWidget::CroppingWidget(QWidget *parent) :
    AbstractFilterWidget(parent),
    ui(new Ui::CroppingWidget)
{
    ui->setupUi(this);
}

CroppingWidget::~CroppingWidget()
{
    delete ui;
}

void CroppingWidget::on_preview_toggled(bool checked)
{
    if (checked) {
        ui->view->resetRectangleMoved();
        emit rectangleChanged();
        ui->view->setPixmap(previewPixmap);
    } else {
        ui->view->setPixmap(inputPixmap);
    }
}

void CroppingWidget::setPixmap(QPixmap pixmap)
{
    inputPixmap = pixmap;
    if (!preview())
        ui->view->setPixmap(pixmap);
}

void CroppingWidget::setPreview(QPixmap pixmap)
{
    previewPixmap = pixmap;
    if (preview())
        ui->view->setPixmap(pixmap);
}

bool CroppingWidget::preview()
{
    return ui->preview->isChecked();
}

QRect CroppingWidget::rectangle()
{
    return ui->view->getRectangle();
}
