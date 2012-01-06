#ifndef DEKEYSTONINGGRAPHICSVIEW_H
#define DEKEYSTONINGGRAPHICSVIEW_H

#include "basefiltergraphicsview.h"
#include "corner.h"
#include "line.h"

class DekeystoningGraphicsView : public BaseFilterGraphicsView
{
public:
    DekeystoningGraphicsView(QWidget *parent);
    qreal meanWidth();
    qreal meanHeight();
    QPolygonF sourcePolygon();
private:
    Corner *c1, *c2, *c3, *c4;
    Line *l1, *l2, *l3, *l4;
};

#endif // DEKEYSTONINGGRAPHICSVIEW_H
