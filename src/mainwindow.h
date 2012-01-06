#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QGraphicsPixmapItem>
#include "corner.h"

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

private:
    Ui::MainWindow *ui;
    QFileSystemModel *FSModel;

public slots:
    void ImageSelected(QModelIndex idx);
    void slotTransform();
};

#endif // MAINWINDOW_H
