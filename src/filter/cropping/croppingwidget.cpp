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

/** \brief Get the filter settings

    NOTE: Currently does only save the polygon coordinates; one may want to save
    activated and preview.
*/
QMap<QString, QVariant> CroppingWidget::getSettings()
{
    return ui->view->getSettings();
}

/** \brief sets the filter settings (change polygon coordinates)

    If the settings are not present, sets default values

    NOTE: Currently does only save the polygon coordinates; one may want to load
    activated and preview settings (if present).
*/
void CroppingWidget::setSettings(QMap<QString, QVariant> settings)
{
    ui->view->setSettings(settings);
}

/** \brief Sets new Selection Color

  This does only forward the information, as this widget ist the only one able to call
  members functions of ui->view.
 */
void CroppingWidget::setSelectionColor(QColor color)
{
    ui->view->setSelectionColor(color);
}
