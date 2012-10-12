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

#ifndef IMAGETABLEWIDGET_H
#define IMAGETABLEWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include "filtercontainer.h"

namespace Ui {
class ImageTableWidget;
}

class ImageTableWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ImageTableWidget(QWidget *parent = 0);
    ~ImageTableWidget();
    void setFilterContainer(FilterContainer *container);
    QMap<QString, QVariant> getSettings();
    void setSettings(QMap<QString, QVariant> settings);
    void clear();
    void exportToFolder(QString folder);
    void exportToPdf(QString pdfFile);


public slots:
    void currentItemChanged(QTableWidgetItem *newItem, QTableWidgetItem *previousItem);

private slots:
    void on_addLeft_clicked();
    void on_addEmptyLeft_clicked();
    void on_addRight_clicked();
    void on_addEmptyRight_clicked();
    void on_upLeft_clicked();
    void on_upRight_clicked();
    void on_downRight_clicked();
    void on_downLeft_clicked();
    void on_remove_clicked();

private:
    Ui::ImageTableWidget *ui;
    enum ImageSide { leftSide, rightSide };
    FilterContainer *filterContainer;
    QString lastDir;
    // stores the last row for left and right images
    int nextRow[2];

    void addImage(QString fileName, enum ImageSide side,
                  QMap<QString, QVariant> settings = QMap<QString, QVariant> ());
    enum ImageTableUserRoles { ImagePreferences = Qt::UserRole,
                              ImageFileName
                            };
    void addClicked(ImageTableWidget::ImageSide side);
    void upClicked(ImageTableWidget::ImageSide side);
    void downClicked(ImageTableWidget::ImageSide side);


signals:
    void pixmapChanged (QPixmap newPixmap);

};

#endif // IMAGETABLEWIDGET_H
