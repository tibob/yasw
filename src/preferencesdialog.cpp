#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDebug>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    setSelectionColor("green");
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

/* TODO: is this the right way to pass the settings? What I need is a reference */
void PreferencesDialog::setSettings(QSettings *newSettings)
{
    QColor color;
    settings = newSettings;

    color = settings->value("selectionColor").value<QColor>();
    if (!color.isValid()) {
        color = selectionColor;
    }
    setSelectionColor(color);
}

void PreferencesDialog::on_selectionColorButton_clicked()
{
    QColor color;

    color = QColorDialog::getColor(selectionColor, this, tr("Choose a color for visual selection"));
    setSelectionColor(color);
}

void PreferencesDialog::setSelectionColor(QColor color)
{
    QPalette palette;

    qDebug() << color;

    if (!color.isValid()) {
        return;
    }

    selectionColor = color;
    palette.setColor(QPalette::ButtonText, color);
    ui->selectionColorButton->setPalette(palette);

    if (settings) {
        settings->setValue("selectionColor", color);
    }

    emit(selectionColorChanged(color));
}
