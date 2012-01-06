#include "basefilterwidget.h"
#include "ui_basefilterwidget.h"

BaseFilterWidget::BaseFilterWidget(QWidget *parent) :
    AbstractFilterWidget(parent),
    ui(new Ui::BaseFilterWidget)
{
    ui->setupUi(this);
}

BaseFilterWidget::~BaseFilterWidget()
{
    delete ui;
}

void BaseFilterWidget::changeEvent(QEvent *e)
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

void BaseFilterWidget::setPixmap(QPixmap pixmap)
{
    ui->view->setPixmap(pixmap);
}

