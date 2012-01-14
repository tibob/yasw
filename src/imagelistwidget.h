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

#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
    class ImageListWidget;
}

class ImageListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageListWidget(QWidget *parent = 0);
    ~ImageListWidget();

public slots:
    void imageClicked (QListWidgetItem * item);

private slots:
    void on_addEmpty_clicked();

    void on_remove_clicked();

    void on_add_clicked();

    void on_up_clicked();

    void on_down_clicked();

private:
    Ui::ImageListWidget *ui;

signals:
    void pixmapChanged (QPixmap newPixmap);
};

#endif // IMAGELISTWIDGET_H
