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

#include "croppingcorner.h"

/*! \class CroppingCorner

  \brief corner of the cropping rectangle

  A cropping rectangle is defined by its top left and bottom right corner.
  When they move, the Rectangle coordinates and size have to be changed.
  */

/*! \brief Creates a Corner for the rectangle

    The corner is a circle (diameter 8 pixel) that can be moved to modify the rectangle.
    It ignores Transformation of the GraphicsView so that it has allways the same size while zooming.
*/
CroppingCorner::CroppingCorner(qreal x, qreal y, int cornerType, QRect *rectangle)
{
    const int Diameter = 8;
    setRect(-Diameter/2, -Diameter/2, Diameter, Diameter);
    setPos(x, y);
    setZValue(100);
    setFlags(ItemIsMovable |
             ItemIgnoresTransformations |
             ItemSendsGeometryChanges);
    this->cornerType = cornerType;
    this->rectangle = rectangle;
    moveRectangle();
}

void CroppingCorner::moveRectangle()
{
    switch (cornerType) {
        case TopLeftCorner:
            rectangle->setTopLeft(scenePos().toPoint());
            break;
        case BottomRightCorner:
            rectangle->setBottomRight(scenePos().toPoint());
            break;
    }
}

bool CroppingCorner::getCornerMoved()
{
    return cornerMoved;
}

void CroppingCorner::resetCornerMoved()
{
    cornerMoved = false;
}

