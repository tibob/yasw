#include "dekeystoninggraphicsview.h"


DekeystoningGraphicsView::DekeystoningGraphicsView(QWidget *parent):
        BaseFilterGraphicsView(parent)
{
    c1 = new Corner(100, 100);
    scene->addItem(c1);

    c2 = new Corner(500, 100);
    scene->addItem(c2);

    c3 = new Corner(500, 500);
    scene->addItem(c3);

    c4 = new Corner(100, 500);
    scene->addItem(c4);

    l1 = new Line(c1, c2);
    l2 = new Line(c2, c3);
    l3 = new Line(c3, c4);
    l4 = new Line(c4, c1);
    scene->addItem(l1);
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);
}

/** \brief Mean width of the transformation polygon.

  This is used as the width of the resulting Pixmap.
*/
qreal DekeystoningGraphicsView::meanWidth()
{
    QLineF line1, line2;

    line1 = QLineF(c1->pos(), c2->pos());
    line2 = QLineF(c3->pos(), c4->pos());

    return (line1.length() + line2.length())/2;

}

/** \brief Mean height of the transformation polygon.

  This is used as the height of the resulting Pixmap.
*/
qreal DekeystoningGraphicsView::meanHeight()
{
    QLineF line1, line2;

    line1 = QLineF(c2->pos(), c3->pos());
    line2 = QLineF(c1->pos(), c4->pos());

    return (line1.length() + line2.length())/2;

}

QPolygonF DekeystoningGraphicsView::sourcePolygon()
{
    QPolygonF polygon;

    polygon << c1->pos() << c2->pos() << c3->pos() << c4->pos();

    return polygon;
}



