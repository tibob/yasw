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
#include "dekeystoninggraphicsview.h"

/*! \class DekeystoningGraphicsView
    \brief Display a polygon over an image for configuring of deykeystoning.

    DekeystoningGraphicsView inherits BaseFilterGraphicsView and its
    features (scene, zooming, setPixmap).
    The polygon can be hidden (to display the preview of the pixmap.
 */

/*! Constructs the polygon, formed of 4 corners (c1..4) and 4 lines (l1..4)
  and adds them to the scene.
  */
DekeystoningGraphicsView::DekeystoningGraphicsView(QWidget *parent):
        BaseFilterGraphicsView(parent)
{
    topLeftCorner = new DekeystoningCorner(defaultTopLeft);
    scene->addItem(topLeftCorner);

    topRightCorner = new DekeystoningCorner(defaultTopRight);
    scene->addItem(topRightCorner);

    bottomRightCorner = new DekeystoningCorner(defaultBottomRight);
    scene->addItem(bottomRightCorner);

    bottomLeftCorner = new DekeystoningCorner(defaultBottomLeft);
    scene->addItem(bottomLeftCorner);

    l1 = new DekeystoningLine(topLeftCorner, topRightCorner);
    l2 = new DekeystoningLine(topRightCorner, bottomRightCorner);
    l3 = new DekeystoningLine(bottomRightCorner, bottomLeftCorner);
    l4 = new DekeystoningLine(bottomLeftCorner, topLeftCorner);
    scene->addItem(l1);
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);

    /* connect the corners together so they can move each other when Control is pressed */
    connect(topLeftCorner, SIGNAL(moveOtherCorner(QPointF)),
            topRightCorner, SLOT(moveCorner(QPointF)));
    connect(topLeftCorner, SIGNAL(moveOtherCorner(QPointF)),
            bottomRightCorner, SLOT(moveCorner(QPointF)));
    connect(topLeftCorner, SIGNAL(moveOtherCorner(QPointF)),
            bottomLeftCorner, SLOT(moveCorner(QPointF)));

    connect(topRightCorner, SIGNAL(moveOtherCorner(QPointF)),
            topLeftCorner, SLOT(moveCorner(QPointF)));
    connect(topRightCorner, SIGNAL(moveOtherCorner(QPointF)),
            bottomRightCorner, SLOT(moveCorner(QPointF)));
    connect(topRightCorner, SIGNAL(moveOtherCorner(QPointF)),
            bottomLeftCorner, SLOT(moveCorner(QPointF)));

    connect(bottomRightCorner, SIGNAL(moveOtherCorner(QPointF)),
            topRightCorner, SLOT(moveCorner(QPointF)));
    connect(bottomRightCorner, SIGNAL(moveOtherCorner(QPointF)),
            topLeftCorner, SLOT(moveCorner(QPointF)));
    connect(bottomRightCorner, SIGNAL(moveOtherCorner(QPointF)),
            bottomLeftCorner, SLOT(moveCorner(QPointF)));

    connect(bottomLeftCorner, SIGNAL(moveOtherCorner(QPointF)),
            topLeftCorner, SLOT(moveCorner(QPointF)));
    connect(bottomLeftCorner, SIGNAL(moveOtherCorner(QPointF)),
            bottomRightCorner, SLOT(moveCorner(QPointF)));
    connect(bottomLeftCorner, SIGNAL(moveOtherCorner(QPointF)),
            topRightCorner, SLOT(moveCorner(QPointF)));
}

/*! cleen the allocated memory */
DekeystoningGraphicsView::~DekeystoningGraphicsView()
{
    delete topLeftCorner;
    delete topRightCorner;
    delete bottomRightCorner;
    delete bottomLeftCorner;
    delete l1;
    delete l2;
    delete l3;
    delete l4;
}

/** \brief Mean width of the transformation polygon.

  This is used as the width of the resulting Pixmap.
*/
qreal DekeystoningGraphicsView::meanWidth()
{
    QLineF line1 = QLineF(topLeftCorner->pos(), topRightCorner->pos());
    QLineF line2 = QLineF(bottomRightCorner->pos(), bottomLeftCorner->pos());

    qreal width = (line1.length() + line2.length())/2;

    return width;
}

/*! \brief Mean height of the transformation polygon.

  This is used as the height of the resulting Pixmap.
*/
qreal DekeystoningGraphicsView::meanHeight()
{
    QLineF line1 = QLineF(topRightCorner->pos(), bottomRightCorner->pos());
    QLineF line2 = QLineF(topLeftCorner->pos(), bottomLeftCorner->pos());

    qreal height = (line1.length() + line2.length())/2;

    return height;
}

/*! \return The polygon as drywed in the scene */
QPolygonF DekeystoningGraphicsView::polygon()
{
    QPolygonF polygon;

    polygon << topLeftCorner->pos() << topRightCorner->pos() << bottomRightCorner->pos() << bottomLeftCorner->pos();

    return polygon;
}

/*! Hides the polygon so that it does not interfere with a previewed Pixmap */
void DekeystoningGraphicsView::hidePolygon(bool hide)
{
    bool showPolygon = !hide;

    topLeftCorner->setVisible(showPolygon);
    topRightCorner->setVisible(showPolygon);
    bottomRightCorner->setVisible(showPolygon);
    bottomLeftCorner->setVisible(showPolygon);
    l1->setVisible(showPolygon);
    l2->setVisible(showPolygon);
    l3->setVisible(showPolygon);
    l4->setVisible(showPolygon);
}

/** \brief Changes the color of the corners and the line.

  This slot is called when changing the selectionColor preference of yasw
*/
void DekeystoningGraphicsView::setSelectionColor(QColor color)
{
    QPen pen = QPen(color);

    topLeftCorner->setPen(pen);
    topRightCorner->setPen(color);
    bottomRightCorner->setPen(color);
    bottomLeftCorner->setPen(color);
    l1->setPen(color);
    l2->setPen(color);
    l3->setPen(color);
    l4->setPen(color);
}

/** \brief Check if polygon moved since last resetPolygonMoved() */
bool DekeystoningGraphicsView::polygonMoved()
{
    return topLeftCorner->getCornerMoved()
            || topRightCorner->getCornerMoved()
            || bottomRightCorner->getCornerMoved()
            || bottomLeftCorner->getCornerMoved();
}

/** \brief Resets all registered moves for the polygon, so that polygonMoved()
returns false */
void DekeystoningGraphicsView::resetPolygonMoved()
{
    topLeftCorner->resetCornerMoved();
    topRightCorner->resetCornerMoved();
    bottomRightCorner->resetCornerMoved();
    bottomLeftCorner->resetCornerMoved();
}

/** \brief Get the filter settings (gets the polygon coordinates)
*/
QMap<QString, QVariant> DekeystoningGraphicsView::getSettings()
{
    QMap<QString, QVariant> settings;
    settings["topLeftCorner"] = topLeftCorner->pos();
    settings["topRightCorner"] = topRightCorner->pos();
    settings["bottomRightCorner"] = bottomRightCorner->pos();
    settings["bottomLeftCorner"] = bottomLeftCorner->pos();

    return settings;
}

/** \brief sets the filter settings (change polygon coordinates)

    If the settings are not present, sets default values
*/
void DekeystoningGraphicsView::setSettings(QMap<QString, QVariant> settings)
{
    if (settings.contains("topLeftCorner")
            && settings["topLeftCorner"].canConvert(QVariant::PointF)) {
        topLeftCorner->setPos(settings["topLeftCorner"].toPointF());
    } else {
        topLeftCorner->setPos(defaultTopLeft);
    }

    if (settings.contains("topRightCorner")
            && settings["topRightCorner"].canConvert(QVariant::PointF)) {
        topRightCorner->setPos(settings["topRightCorner"].toPointF());
    } else {
        topRightCorner->setPos(defaultTopRight);
    }

    if (settings.contains("bottomRightCorner")
            && settings["bottomRightCorner"].canConvert(QVariant::PointF)) {
        bottomRightCorner->setPos(settings["bottomRightCorner"].toPointF());
    } else {
        bottomRightCorner->setPos(defaultBottomRight);
    }

    if (settings.contains("bottomLeftCorner")
            && settings["bottomLeftCorner"].canConvert(QVariant::PointF)) {
        bottomLeftCorner->setPos(settings["bottomLeftCorner"].toPointF());
    } else {
        bottomLeftCorner->setPos(defaultBottomLeft);
    }
}



