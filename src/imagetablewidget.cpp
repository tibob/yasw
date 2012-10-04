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

#include <QFileInfo>
#include <QFileDialog>
#include "imagetablewidget.h"
#include "ui_imagetablewidget.h"

ImageTableWidget::ImageTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageTableWidget)
{
    ui->setupUi(this);

    connect(ui->images, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),
            this, SLOT(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)));

    filterContainer = NULL;

    nextRow[leftSide] = 0;
    nextRow[rightSide] = 0;

    ui->images->setHorizontalHeaderLabels(QStringList() << "Left" << "Right");
}

ImageTableWidget::~ImageTableWidget()
{
    delete ui;
}

void ImageTableWidget::setFilterContainer(FilterContainer *container)
{
    if (filterContainer) {
        disconnect(this, SIGNAL(pixmapChanged(QPixmap)),
                   filterContainer, SLOT(setImage(QPixmap)));
    }

    filterContainer = container;

    connect (this, SIGNAL(pixmapChanged(QPixmap)),
             filterContainer, SLOT(setImage(QPixmap)));
}



void ImageTableWidget::currentItemChanged(QTableWidgetItem *newItem, QTableWidgetItem *previousItem)
{
    QMap<QString, QVariant> settings;
    int rowPreviousItem, sidePreviousItem, i;

    if (filterContainer && previousItem) {
        settings = filterContainer->getSettings();
        // settings changed? Save them!
        if (settings != previousItem->data(ImagePreferences).toMap()) {
            previousItem->setData(ImagePreferences, settings);

            // Propagate settings according to settings policy
            switch (ui->settingPolicy->currentIndex()) {
                case 1: // propagate to all following images
                    rowPreviousItem = ui->images->row(previousItem);
                    sidePreviousItem = ui->images->column(previousItem);
                    for (i = rowPreviousItem; i < nextRow[sidePreviousItem]; i++) {
                        ui->images->item(i, sidePreviousItem)->setData(ImagePreferences, settings);
                    }
                    break;
                case 2: // propagate to all images
                    for (i = 0; i < nextRow[leftSide]; i++) {
                        ui->images->item(i, leftSide)->setData(ImagePreferences, settings);
                    }
                    for (i = 0; i < nextRow[rightSide]; i++) {
                        ui->images->item(i, rightSide)->setData(ImagePreferences, settings);
                    }
                    break;
                //case 0: do not propagate;
            }
        }
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

void ImageTableWidget::on_addLeft_clicked()
{
    addClicked(leftSide);
}

//FIXME: should insert at the current position, not append
void ImageTableWidget::addClicked(ImageTableWidget::ImageSide side)
{
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
        addImage(imageFileName, side);
    }

    if (imageFileName.length() > 0) {
        fi = QFileInfo(imageFileName);
        lastDir = fi.absolutePath();
    }

}


// FIXME: handle fileName = "" (empty image)
void ImageTableWidget::addImage(QString fileName, ImageTableWidget::ImageSide side, QMap<QString, QVariant> settings)
{
    QTableWidgetItem *item;
    QTableWidgetItem *currentItem;
    QFileInfo fi(fileName);
    QPixmap icon;
    int i, currentRow;

    //NOTE: loading all icons at this time implies waiting time for the user.
    //Alternatives: put some "waiting" dialog or do ICON-loading in the background
    icon = QPixmap(fileName).scaledToWidth(100);
    item = new QTableWidgetItem(QIcon(icon),
                        fi.baseName());

    // Adjust Table size if necessary
    if (nextRow[side] >=  ui->images->rowCount()) {
        ui->images->setRowCount(nextRow[side] + 1);
    }

    currentItem = ui->images->currentItem();
    if (currentItem && ui->images->currentColumn() == side) {
        // Insert before current item
        currentRow = ui->images->currentRow();
    } else {
        // Insert at the End
        currentRow = nextRow[side];
    }

    // move all items after current item one step down
    for (i = nextRow[side]; i > currentRow; i--) {
        ui->images->setItem(i, side, ui->images->takeItem(i - 1, side));
    }

    ui->images->setItem(currentRow, side, item);
    item->setData(ImageFileName, fileName);
    item->setData(ImagePreferences, settings);
    item->setToolTip(fileName);
    nextRow[side] = nextRow[side] + 1;

    if (currentItem)
        ui->images->setCurrentItem(currentItem);
}

void ImageTableWidget::on_addEmptyLeft_clicked()
{
    addImage("", leftSide);
}


void ImageTableWidget::on_addRight_clicked()
{
    addClicked(rightSide);
}

void ImageTableWidget::on_addEmptyRight_clicked()
{
    addImage("", rightSide);
}

void ImageTableWidget::downClicked(ImageTableWidget::ImageSide side)
{
    int currentRow = ui->images->currentRow();
    if (currentRow + 1 > nextRow[side] - 1) {
        return;
    }
    QTableWidgetItem *itemToDown = ui->images->takeItem(currentRow, side);
    QTableWidgetItem *itemToUp = ui->images->takeItem(currentRow + 1, side);
    ui->images->setItem(currentRow +1, side, itemToDown);
    ui->images->setItem(currentRow, side, itemToUp);
    ui->images->setCurrentItem(itemToDown);
}

void ImageTableWidget::upClicked(ImageTableWidget::ImageSide side)
{
    int currentRow = ui->images->currentRow();
    if (currentRow < 1 || currentRow >= nextRow[side]) {
        return;
    }
    QTableWidgetItem *itemToUp = ui->images->takeItem(currentRow, side);
    QTableWidgetItem *itemToDown = ui->images->takeItem(currentRow -1, side);
    ui->images->setItem(currentRow - 1, side, itemToUp);
    ui->images->setItem(currentRow, side, itemToDown);
    ui->images->setCurrentItem(itemToUp);
}

void ImageTableWidget::on_upLeft_clicked()
{
    upClicked(leftSide);
}

void ImageTableWidget::on_upRight_clicked()
{
    upClicked(rightSide);
}

void ImageTableWidget::on_downLeft_clicked()
{
    downClicked(leftSide);
}

void ImageTableWidget::on_downRight_clicked()
{
    downClicked(rightSide);
}

void ImageTableWidget::on_remove_clicked()
{
    int currentRow = ui->images->currentRow();
    int currentColumn = ui->images->currentColumn();
    int otherSide = 1 - currentColumn;
    int i;

    delete ui->images->takeItem(currentRow, currentColumn);
    for (i = currentRow; i < nextRow[currentColumn] - 1; i++) {
        ui->images->setItem(i, currentColumn,
                            ui->images->takeItem(i + 1, currentColumn));
    }
    nextRow[currentColumn]--;
    if (nextRow[currentColumn] >= nextRow[otherSide]) {
        ui->images->setRowCount(nextRow[currentColumn]);
    }
}

QMap<QString, QVariant> ImageTableWidget::getSettings()
{
    QMap<QString, QVariant> settings;
    QTableWidgetItem *item;
    int row;
    QString key;

    // Save the settings of current filter before saving
    settings = filterContainer->getSettings();
    item = ui->images->currentItem();
    if (item)
        item->setData(ImagePreferences, settings);
    settings.clear();

    for (row = 0; row < nextRow[leftSide]; row++) {
        item = ui->images->item(row, leftSide);
        key = QString("%1_Left_").arg(row, leftSide) + item->data(ImageFileName).toString();
        settings[key] = item->data(ImagePreferences).toMap();
    }
    for (row = 0; row < nextRow[rightSide]; row++) {
        item = ui->images->item(row, rightSide);
        key = QString("%1_Right_").arg(row, rightSide) + item->data(ImageFileName).toString();
        settings[key] = item->data(ImagePreferences).toMap();
    }

    return settings;
}

void ImageTableWidget::setSettings(QMap<QString, QVariant> settings)
{
    QString key;
    int row;
    QString sideString;
    ImageTableWidget::ImageSide side;
    QString filename;

    clear();

    foreach (key, settings.keys()) {
        row = key.section("_", 0, 0).toInt();
        sideString = key.section("_", 1, 1);
        if (sideString == "Left") {
            side = leftSide;
        } else {
            //NOTE: this is not nice, we should check if sideString == "Right"
            side = rightSide;
        }
        filename = key.section("_", 2);
        if (row >= 0 && filename.length() > 0) {
            addImage(filename, side, settings[key].toMap());
        }
    }
}

void ImageTableWidget::clear()
{
    //FIXME: is memory cleared?
    ui->images->setRowCount(0);
    nextRow[leftSide] = 0;
    nextRow[rightSide] = 0;
}

void ImageTableWidget::exportToFolder(QString folder)
{
    int row;
    QTableWidgetItem *currentItem = ui->images->currentItem();
    QPixmap pixmap;
    QString filename;

    for (row = 0; row < nextRow[leftSide]; row++) {
        ui->images->setCurrentCell(row, leftSide);
        pixmap = filterContainer->getResultImage();
        filename = QString("%1/image_%2_Left.jpg").arg(folder).arg(row+1, 3, 10, QChar('0'));
        pixmap.save(filename);
    }
    for (row = 0; row < nextRow[rightSide]; row++) {
        ui->images->setCurrentCell(row, rightSide);
        pixmap = filterContainer->getResultImage();
        filename = QString("%1/image_%2_Right.jpg").arg(folder).arg(row+1, 3, 10, QChar('0'));
        pixmap.save(filename);
    }

    ui->images->setCurrentItem(currentItem);
}
