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
    ui->view->setPixmap(pixmap);
}

