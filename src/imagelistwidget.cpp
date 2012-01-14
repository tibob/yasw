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

#include "imagelistwidget.h"
#include "ui_imagelistwidget.h"
#include <QFileDialog>

ImageListWidget::ImageListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageListWidget)
{
    ui->setupUi(this);
    ui->images->setIconSize(QSize(100, 100));
    ui->images->setSpacing(1);

    connect(ui->images, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(imageClicked(QListWidgetItem*)));
}

ImageListWidget::~ImageListWidget()
{
    delete ui;
}

void ImageListWidget::on_addEmpty_clicked()
{
    QListWidgetItem *emptyItem = new QListWidgetItem(QIcon(":/icons/tango-icon-theme/document-new.svg"),
                        tr("(Empty placeholder)"));
    int currentRow = ui->images->currentRow();
    ui->images->insertItem(currentRow, emptyItem);
}

void ImageListWidget::on_remove_clicked()
{
    delete ui->images->currentItem();
}

void ImageListWidget::on_add_clicked()
{
    QStringList images = QFileDialog::getOpenFileNames(this,
                        tr("Choose images"),
                        QDir::currentPath(),
                        tr("Images (*.jpg)"));

    foreach (QString image, images) {
        new QListWidgetItem(QIcon(image),
                            image,
                            ui->images);

    }
}

void ImageListWidget::on_up_clicked()
{
    int currentRow = ui->images->currentRow();
    QListWidgetItem *item = ui->images->takeItem(currentRow);
    ui->images->insertItem(currentRow - 1, item);
    ui->images->setCurrentItem(item);
}

void ImageListWidget::on_down_clicked()
{
    int currentRow = ui->images->currentRow();
    QListWidgetItem *item = ui->images->takeItem(currentRow);
    ui->images->insertItem(currentRow + 1, item);
    ui->images->setCurrentItem(item);
}

void ImageListWidget::imageClicked(QListWidgetItem *item)
{
    emit pixmapChanged(QPixmap(item->text()));
}
