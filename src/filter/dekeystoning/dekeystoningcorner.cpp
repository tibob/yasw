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

#include "dekeystoningcorner.h"
#include "dekeystoningline.h"

/*! \class DekeystoningCorner
    \brief Corner to build a polygon

    The corner is a circle (diameter 8 pixel) that can be moved to modify the lines
    connected to it (via Line::trackCorner). All the corner together build a polygon,
    wich moves with it.
    Corner is q QGraphicsItem wich is to be used in a QGraphicsScene/View.

    It ignores Transformation of the GraphicsView so that it has allways the same
    size while zooming.
*/
DekeystoningCorner::DekeystoningCorner(QPoint position)
{
    setRect(-diameter/2, -diameter/2, diameter, diameter);
    setPos(position);
    setZValue(100);
    setFlags(ItemIsMovable |
             ItemIgnoresTransformations |
             ItemSendsGeometryChanges);
}

/** \brief Registers a line ending at this corner.
 This is called from the DekeystoningLine itself

*/
void DekeystoningCorner::registerLine(DekeystoningLine *line)
{
    myLines.insert(line);
}

/*! \brief Handle Corner moves

    itemChanged ist called because the Flag ItemSendsGeometryChanges is set.
    When called, it will update the position of the sides of the Polygon (Line)
    and register that the Corner moved so that the transformation Matrix and the output Pixmap
    has to be recalculated.
*/
QVariant DekeystoningCorner::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        cornerMoved = true;
        foreach (DekeystoningLine *line, myLines)
            line->trackCorners();
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void DekeystoningCorner::resetCornerMoved()
{
    cornerMoved = false;
}

bool DekeystoningCorner::getCornerMoved()
{
    return cornerMoved;
}


