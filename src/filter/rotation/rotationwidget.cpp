/*
 * Copyright (C) 2012 Robert Chéramy (robert@cheramy.net)
 *
 * This file is part of YASW (Yet Another Scan Wizard).
 *
 * YASW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * YASW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with YASW.  If not, see <http://www.gnu.org/licenses/>.
 */
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
    emit rotationChanged();
}

void RotationWidget::on_rotateRight_clicked()
{
    rotationAngle = (rotationAngle + 90) % 360;;
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

