#include "corner.h"
#include "line.h"

Corner::Corner(qreal x, qreal y)
{
    const int Diameter = 8;
    this->x = x;
    this->y = y;
//    setRect(x-Diameter/2, y-Diameter/2, Diameter, Diameter);
    setRect(-Diameter/2, -Diameter/2, Diameter, Diameter);
    setPos(x, y);
    setZValue(100);
    setFlags(ItemIsMovable |
             ItemIgnoresTransformations |  // no use, I have to fix the diameter for myself
             ItemSendsGeometryChanges);
}


void Corner::addLine(Line *line)
{
    myLines.insert(line);
}

void Corner::removeLine(Line *line)
{
    myLines.remove(line);
}


QVariant Corner::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        foreach (Line *line, myLines)
            line->trackCorners();
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}


