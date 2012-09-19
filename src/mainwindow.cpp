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

/** todo:
Read File format should include png
*/

#include <QDebug>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "corner.h"
#include "line.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageList->setFilterContainer(ui->filterContainer);
}

MainWindow::~MainWindow()
{
    delete ui;
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

/** \brief Save the current project
 \\TODO: save all images; ask for filename if not defined...
*/
void MainWindow::on_action_Save_triggered()
{
    QMap<QString, QVariant> settings;

    settings = ui->filterContainer->getSettings();

    // FIXME: Save QStreqm version and yast Version
    QFile file("filesetting.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << settings;
        file.close();
    }

}

/** \brief Open a project from file
 //TODO: clear current project; load all images...
 */

void MainWindow::on_action_Open_triggered()
{
    QMap<QString, QVariant> settings;

    // FIXME: Load and check QStream version and yast Version
    QFile file("filesetting.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> settings;
        file.close();
    }

    ui->filterContainer->setSettings(settings);
}
