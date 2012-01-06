#include <QPen>

#include "line.h"
#include "corner.h"

Line::Line(Corner *from, Corner *to)
{
    fromCorner = from;
    fromCorner->addLine(this);
    toCorner = to;
    toCorner->addLine(this);

    trackCorners();
}

void Line::trackCorners()
{
    setLine(QLineF(fromCorner->scenePos(), toCorner->scenePos()));
}


