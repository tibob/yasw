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
#include <QApplication>

/*! \class CroppingCorner

  \brief corner of the cropping rectangle

  A cropping rectangle is defined by its top left and bottom right corner.
  When they move, the Rectangle coordinates and size have to be changed.
  */

/*! \brief Creates a Corner for the rectangle

    The corner is a circle (diameter 8 pixel) that can be moved to modify the rectangle.
    It ignores Transformation of the GraphicsView so that it has allways the same size while zooming.
*/
CroppingCorner::CroppingCorner(QPoint position)
{
    setRect(-diameter/2, -diameter/2, diameter, diameter);
    setPos(position);
    lastPosition = pos();
    setZValue(100);
    setFlags(ItemIsMovable |
             ItemIgnoresTransformations |
             ItemSendsGeometryChanges);
}

bool CroppingCorner::getCornerMoved()
{
    return cornerMoved;
}

void CroppingCorner::resetCornerMoved()
{
    cornerMoved = false;
}


QVariant CroppingCorner::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        Qt::KeyboardModifiers keyMod = QApplication::keyboardModifiers ();
        if (keyMod.testFlag(Qt::ControlModifier)) {
            QPointF positionDelta = pos() - lastPosition;
            emit moveOtherCorner(positionDelta);
        }
        cornerMoved = true;
        emit signalCornerMoved();
        lastPosition = pos();
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}


void CroppingCorner::moveCorner(QPointF delta)
{
    /* deativate change notifications */
    setFlag(ItemSendsGeometryChanges, false);
    /* move the Corner */
    setPos(pos() + delta);
    /* Update cornerMoved, lastPosition and rectangle */
    cornerMoved = true;
    emit signalCornerMoved();
    lastPosition = pos();
    /* reactivate change notifications */
    setFlag(ItemSendsGeometryChanges, true);
}
