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
#include "croppinggraphicsview.h"

CroppingGraphicsView::CroppingGraphicsView(QWidget *parent) :
    BaseFilterGraphicsView(parent)
{
    topLeftCorner = new CroppingCorner(defaultTopLeft); //, TopLeftCorner, &rectangle);
    scene->addItem(topLeftCorner);

    bottomRightCorner = new CroppingCorner(defaultBottomRight); //, BottomRightCorner, &rectangle);
    scene->addItem(bottomRightCorner);

    rectangle = new QGraphicsRectItem();
    scene->addItem(rectangle);

    connect(topLeftCorner, SIGNAL(signalCornerMoved()), this, SLOT(moveRectangle()));
    connect(bottomRightCorner, SIGNAL(signalCornerMoved()), this, SLOT(moveRectangle()));
    moveRectangle();

    /* connect the corners together so they can move each other when Control is pressed */
    connect(topLeftCorner, SIGNAL(moveOtherCorner(QPointF)),
            bottomRightCorner, SLOT(moveCorner(QPointF)));
    connect(bottomRightCorner, SIGNAL(moveOtherCorner(QPointF)),
            topLeftCorner, SLOT(moveCorner(QPointF)));
}

CroppingGraphicsView::~CroppingGraphicsView()
{
    delete topLeftCorner;
    delete bottomRightCorner;
    delete rectangle;
}

QRect CroppingGraphicsView::getRectangle()
{
    return QRect(topLeftCorner->scenePos().toPoint(),
                 bottomRightCorner->scenePos().toPoint());
}

void CroppingGraphicsView::resetRectangleMoved()
{
    topLeftCorner->resetCornerMoved();
    bottomRightCorner->resetCornerMoved();
}

bool CroppingGraphicsView::rectangleMoved()
{
    return topLeftCorner->getCornerMoved()
            || bottomRightCorner->getCornerMoved();
}

void CroppingGraphicsView::hideRectangle(bool hide)
{
    bool showRectangle = !hide;

    topLeftCorner->setVisible(showRectangle);
    bottomRightCorner->setVisible(showRectangle);
    rectangle->setVisible(showRectangle);
}

void CroppingGraphicsView::moveRectangle()
{
    qreal width = bottomRightCorner->x()-topLeftCorner->x();
    qreal heigth = bottomRightCorner->y()-topLeftCorner->y();

    rectangle->setRect(0, 0, width, heigth);
    rectangle->setPos(topLeftCorner->scenePos());
}


/** \brief Get the filter settings (gets the polygon coordinates)
*/
QMap<QString, QVariant> CroppingGraphicsView::getSettings()
{
    QMap<QString, QVariant> settings;

    settings["bottomRightCorner"] =  bottomRightCorner->pos();
    settings["topLeftCorner"] =  topLeftCorner->pos();

    return settings;
}

/** \brief sets the filter settings (change polygon coordinates)

    If the settings are not present, sets default values
*/
void CroppingGraphicsView::setSettings(QMap<QString, QVariant> settings)
{
    if (settings.contains("bottomRightCorner") && settings["bottomRightCorner"].canConvert(QVariant::PointF)) {
        bottomRightCorner->setPos(settings["bottomRightCorner"].toPointF());
    } else {
        bottomRightCorner->setPos(defaultBottomRight);
    }

    if (settings.contains("topLeftCorner") && settings["topLeftCorner"].canConvert(QVariant::PointF)) {
        topLeftCorner->setPos(settings["topLeftCorner"].toPointF());
    } else {
        topLeftCorner->setPos(defaultTopLeft);
    }
}

void CroppingGraphicsView::setSelectionColor(QColor color)
{
    QPen pen = QPen(color);

    topLeftCorner->setPen(pen);
    bottomRightCorner->setPen(pen);
    rectangle->setPen(pen);
}

