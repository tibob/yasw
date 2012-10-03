#include <QFileInfo>
#include <QFileDialog>
#include "imagetablewidget.h"
#include "ui_imagetablewidget.h"

ImageTableWidget::ImageTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageTableWidget)
{
    ui->setupUi(this);

//    connect(ui->images, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
//            this, SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));

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
    QFileInfo fi(fileName);
    QPixmap icon;

    //NOTE: loading all icons at this time implies waiting time for the user.
    //Alternatives: put some "waiting" dialog or do ICON-loading in the background
    icon = QPixmap(fileName).scaledToWidth(100);
    item = new QTableWidgetItem(QIcon(icon),
                        fi.baseName());

    // Adjust Table size if necessary
    if (nextRow[side] >=  ui->images->rowCount()) {
        ui->images->setRowCount(nextRow[side] + 1);
    }
    ui->images->setItem(nextRow[side], side, item);
    item->setData(ImageFileName, fileName);
    item->setData(ImagePreferences, settings);
    item->setToolTip(fileName);
    nextRow[side] = nextRow[side] + 1;
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
    if (currentRow < 1) {
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
