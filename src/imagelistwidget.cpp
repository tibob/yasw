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
#include <QFileInfo>
#include <QDebug>

/** \class ImageListWidget
    \brief Widget that handle out list of images and display them as icons.

 ImageListWidget will handle and store the filter settings for each image.
 In each ImageListWidgetItem, we store the Filename and the Preferences as UserData (see ImageListUserRoles).
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

/** Creates an empty image (placeholder for example for
    an empty page wich has not been scaned) */
void ImageListWidget::on_addEmpty_clicked()
{
    QListWidgetItem *emptyItem = new QListWidgetItem(QIcon(":/icons/tango-icon-theme/document-new.svg"),
                        tr("(Empty placeholder)"));
    int currentRow = ui->images->currentRow();
    ui->images->insertItem(currentRow, emptyItem);
}

/** Removes the current selected image */
void ImageListWidget::on_remove_clicked()
{
    delete ui->images->currentItem();
}

void ImageListWidget::on_add_clicked()
{
    QListWidgetItem *item;
    QFileInfo fi;
    QString imageFileName;

    if (lastDir.length() == 0)
        lastDir = QDir::currentPath();


    QStringList images = QFileDialog::getOpenFileNames(this,
                        tr("Choose images"),
                        lastDir,
                        // FIXME: scaling down for *.png does not work as good as for jpg
                        tr("Images (*.jpg *.png);;All files (* *.*)"));

    foreach (imageFileName, images) {
        item = new QListWidgetItem(QIcon(imageFileName),
                            "",
                            ui->images);
        item->setToolTip(imageFileName);
        item->setData(ImageFileName, imageFileName);
    }

    if (imageFileName.length() != 0) {
        fi = QFileInfo(imageFileName);
        lastDir = fi.absolutePath();
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
        emit pixmapChanged(QPixmap(newItem->data(ImageFileName).toString()));
    } else {
        emit pixmapChanged(QPixmap());
        // Reset Filter Settings as no image is selected
        if (filterContainer)
            filterContainer->setSettings(QMap<QString, QVariant>());
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

/** \brief Get settings from all images of the project
 */
QMap<QString, QVariant> ImageListWidget::getSettings()
{
    QMap<QString, QVariant> settings;
    QListWidgetItem *item;
    int index;
    QString key;

    // Save the settings of current filter before saving
    settings = filterContainer->getSettings();
    ui->images->currentItem()->setData(ImagePreferences, settings);

    for (index = 0; index < ui->images->count(); index++) {
        item = ui->images->item(index);
        key = QString("%1_").arg(index + 1) + item->data(ImageFileName).toString();
        settings[key] = item->data(ImagePreferences).toMap();
    }
    return settings;
}

/** \brief Load a new Project from settings
 */
void ImageListWidget::setSettings(QMap<QString, QVariant> settings)
{
    QString key;
    int index;
    QString filename;
    QListWidgetItem *item;

    ui->images->clear();

    foreach (key, settings.keys()) {
        index = key.section("_", 0, 0).toInt();
        filename = key.section("_", 1);
        qDebug() << index << filename;
        if (index > 0 && filename.length() > 0) {
            //NOTE: define a global method to add an image with arguments.
            item = new QListWidgetItem(QIcon(filename),
                                "",
                                ui->images);
            item->setData(ImagePreferences, settings[key]);
            item->setData(ImageFileName, filename);
            item->setToolTip(filename);
            qDebug() << settings[key];
        }
    }
}
