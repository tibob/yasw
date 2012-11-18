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

#include <QChar>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageList->setFilterContainer(ui->filterContainer);

    showMaximized();
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
*/
void MainWindow::on_action_Save_triggered()
{
    if (projectFileName.length() != 0) {
        saveProjectSettings(projectFileName);
    } else {
        on_action_SaveAs_triggered();
    }
}

/** \brief Save the current project in a new file
*/
void MainWindow::on_action_SaveAs_triggered()
{

    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               // FIXME: use last project name
                               // FIXME: save last path
                               QDir::currentPath() + "/project.yasw",
                               tr("yasw projects (*.yasw);;All files (* *.*"));

    if (fileName.length() == 0)
        return;

    //If saving to file was successfull, store the project filename in a global variable
    if (saveProjectSettings(fileName))
        setProjectFileName(fileName);
}

/** \brief Save project settings to file

  @returns true if successful; false on failure
  This private member is used to avoid dupplicate code betwenn save and save as.

  */
bool MainWindow::saveProjectSettings(QString fileName)
{
    QMap<QString, QVariant> settings;

    settings = ui->imageList->getSettings();

    // FIXME: Save QStream version and yast Version
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << settings;
        file.close();
        return true;
    }
    // else, we signal a failure
    QMessageBox::critical(this,
        tr("Could not save Project"),
        tr("A problem occured while saving file \"%1\". The project could not be saved")
                      .arg(fileName)
                          );
    return false;
}

void MainWindow::setProjectFileName(QString fileName)
{
    QFileInfo fi(fileName);

    projectFileName = fileName;

    if (fileName.length() > 0)
        setWindowTitle(tr("yasw - %1").arg(fi.fileName()));
    else
        setWindowTitle(tr("yasw - new project"));
}


/** \brief Open a project from file
 // FIXME: Load and Check QStream version and yasw Version
 */

void MainWindow::on_action_Open_triggered()
{
    QMap<QString, QVariant> settings;

    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Choose project"),
                        QDir::currentPath(),   // FIXME: save last path
                        tr("yasw projects (*.yasw);;All files (* *.*"));
    if (fileName.length() == 0) // Cancel pressed
        return;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> settings;
        file.close();
    }
    setProjectFileName(fileName);

    ui->imageList->setSettings(settings);
}


void MainWindow::exportToJpeg()
{
    QString exportFolder = QFileDialog::getExistingDirectory(this,
                tr("Choose folder for export"),
                QDir::currentPath()  // FIXME: save last path
                );

    if (exportFolder.length() == 0)
        return;

    ui->imageList->exportToFolder(exportFolder);

    QMessageBox::information(this,
                tr("Project exported"),
                tr("The project was exported to folder %1").arg(exportFolder)
                             );
}

void MainWindow::exportToPdf()
{
    QString exportFile = QFileDialog::getSaveFileName(this, tr("Export to PDF"),
                               // FIXME: use project name
                               // FIXME: save last path
                               QDir::currentPath() + "/file.pdf",
                               tr("PDF Files (*.pdf);;All files (* *.*"));

    if (exportFile.length() == 0)
        return;

    ui->imageList->exportToPdf(exportFile);

    QMessageBox::information(this,
                tr("Project exported"),
                tr("The project was exported to file %1").arg(exportFile)
                );
}

/** \brief Close curent project,
    reset settings to default values */
void MainWindow::on_action_Close_triggered()
{
    ui->imageList->clear();
    setProjectFileName("");
}
