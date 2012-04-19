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

/*! \todo use Roles to store data from the filters
  Qt::UserRole (0) = filename of picture
  +1 = QMap<QString, QMap<QString, QVariant> to store filter settings map["filter name"]["setting"] = value
  */
ImageListWidget::ImageListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageListWidget)
{
    ui->setupUi(this);
    ui->images->setIconSize(QSize(100, 100));
    ui->images->setSpacing(1);

    connect(ui->images, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));

    filterContainer = NULL;
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

/** \todo Clear FilterContainer on last Item */
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

/** \brief Change the Image beeing worked on.

    This slot is connected to QListWidget::itemClicked. It saves the settings
    of previous image and restore the settings of the clicked image.
 */
void ImageListWidget::currentItemChanged(QListWidgetItem *newItem, QListWidgetItem *previousItem)
{
    QMap<QString, QVariant> settings;

    if (filterContainer && previousItem) {
        settings = filterContainer->getSettings();
        previousItem->setData(ImagePreferences, settings);
    }

    if (filterContainer && newItem) {
        filterContainer->setSettings(newItem->data(ImagePreferences).toMap());
    }

    if (newItem) {
        emit pixmapChanged(QPixmap(newItem->text()));
    } else {
        emit pixmapChanged(QPixmap());
    }
}

/** \brief Sets the FilterContainer this image list has to interact with.

    As the image list has to get the settings from the FilterContainer, a link
    with signals ans slots is not working.
*/
void ImageListWidget::setFilterContainer(FilterContainer *container)
{
    if (filterContainer) {
        disconnect(this, SIGNAL(pixmapChanged(QPixmap)),
                   filterContainer, SLOT(setImage(QPixmap)));
    }

    filterContainer = container;

    connect (this, SIGNAL(pixmapChanged(QPixmap)),
             filterContainer, SLOT(setImage(QPixmap)));
}
