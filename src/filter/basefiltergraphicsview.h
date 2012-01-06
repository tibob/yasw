#ifndef BASEFILTERGRAPHICSVIEW_H
#define BASEFILTERGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>


class BaseFilterGraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    BaseFilterGraphicsView(QWidget *parent);
    void setPixmap(const QPixmap pixmap);
protected:
    void wheelEvent(QWheelEvent *event);
    QGraphicsScene *scene;
private:
    QGraphicsPixmapItem *pixmapItem;
};

#endif // BASEFILTERGRAPHICSVIEW_H
