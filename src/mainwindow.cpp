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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "corner.h"
#include "line.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FSModel = new QFileSystemModel;
    FSModel->setRootPath(QDir::currentPath());
    FSModel->setNameFilters(QStringList("*.jpg"));
    FSModel->setNameFilterDisables(false);

    ui->fileview->setModel(FSModel);

    ui->fileview->setRootIndex(FSModel->index(QDir::currentPath()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete FSModel;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::ImageSelected(QModelIndex idx)
{
    QString filename = FSModel->filePath(idx);
    ui->statusBar->showMessage(filename, 2000);

    QPixmap image = QPixmap(filename);
    ui->filterContainer->setImage(image);
}

void MainWindow::slotTransform()
{
//    QPixmap result = ui->graphicsView->resultPage();
//
//    QGraphicsScene *scene = new QGraphicsScene();
//    scene->setSceneRect(0, 0, result.width(), result.height());
//    ui->resultView->setScene(scene);
//
//    QGraphicsPixmapItem *pict = new QGraphicsPixmapItem(result);
//    scene->addItem(pict);
//
//    ui->resultView->fitInView(pict);
}

