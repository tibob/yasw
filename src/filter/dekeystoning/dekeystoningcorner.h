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
#ifndef DEKEYSTONINGCORNER_H
#define DEKEYSTONINGCORNER_H

#include <QGraphicsEllipseItem>
#include <QWheelEvent>
#include <QPoint>
#include <QPointF>

class DekeystoningLine;

/*! Inherits QObject to be able to emit and receive signals */
class DekeystoningCorner : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    DekeystoningCorner(QPoint position);
    void registerLine(DekeystoningLine *line);
    bool getCornerMoved();
    void resetCornerMoved();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QSet<DekeystoningLine *> myLines;
    bool cornerMoved;
    const int diameter = 8;
    QPointF lastPosition;
public slots:
    void moveCorner(QPointF delta);

signals:
    /** \brief signal emited when a corner was moved and other corner have to change their position.

    This signal is connected to the slot DekeystoningCorner::moveCorner() of the three other
    coners. The connection is handeld in the constructor of DekeystoningGraphicsView.
     */
    void moveOtherCorner(QPointF delta);
};

#endif // DEKEYSTONINGCORNER_H
