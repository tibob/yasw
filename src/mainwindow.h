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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QGraphicsPixmapItem>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_action_Save_triggered();
    void on_action_Open_triggered();
    void on_action_SaveAs_triggered();
    void on_action_Close_triggered();

    void exportToJpeg();
    void exportToPdf();

    void on_action_About_triggered();

    void openRecentProject();

private:
    bool saveProjectSettings(QString fileName);
    void setProjectFileName(QString fileName);

    void addRecentProject(QString fileName);
    void loadProject(QString fileName);

    Ui::MainWindow *ui;
    QString projectFileName;
    QSettings *settings;
    const int MAX_RECENT_PROJECTS = 5;
};

#endif // MAINWINDOW_H
