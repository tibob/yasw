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
//    QMap<QString, QVariant> getSettings();
//    void setSettings(QMap<QString, QVariant> settings);
//    int size();
//    void focusItem(int index);
//    void clear();

public slots:
//    void currentItemChanged(QTableWidgetItem *newItem, QTableWidgetItem *previousItem);

private slots:
    //FIXME: to implement left / right
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
