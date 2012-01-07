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
        cornerMoved = true;
        foreach (Line *line, myLines)
            line->trackCorners();
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void Corner::resetCornerMoved()
{
    cornerMoved = false;
}

bool Corner::getCornerMoved()
{
    return cornerMoved;
}


