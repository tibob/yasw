#include "dekeystoningwidget.h"
#include "ui_dekeystoningwidget.h"

DekeystoningWidget::DekeystoningWidget(QWidget *parent) :
    AbstractFilterWidget(parent),
    ui(new Ui::DekeystoningWidget)
{
    ui->setupUi(this);
}

DekeystoningWidget::~DekeystoningWidget()
{
    delete ui;
}

void DekeystoningWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DekeystoningWidget::setPixmap(QPixmap pixmap)
{
    inputPixmap = pixmap;
    if (!preview())
        ui->view->setPixmap(pixmap);
}

void DekeystoningWidget::setPreview(QPixmap pixmap)
{
    previewPixmap = pixmap;
    if (preview())
        ui->view->setPixmap(pixmap);
}

qreal DekeystoningWidget::meanWidth()
{
    return ui->view->meanWidth();
}

qreal DekeystoningWidget::meanHeight()
{
    return ui->view->meanHeight();
}

QPolygonF DekeystoningWidget::polygon()
{
    return ui->view->polygon();
}

bool DekeystoningWidget::preview()
{
    return ui->preview->isChecked();
}

void DekeystoningWidget::on_preview_toggled(bool checked)
{
    if (checked) {
        ui->view->resetPolygonMoved();
        emit polygonChanged();
        ui->view->setPixmap(previewPixmap);
    } else {
        ui->view->setPixmap(inputPixmap);
    }
}

bool DekeystoningWidget::polygonMoved()
{
    return ui->view->polygonMoved();
}

void DekeystoningWidget::resetPolygonMoved()
{
    return ui->view->resetPolygonMoved();
}


