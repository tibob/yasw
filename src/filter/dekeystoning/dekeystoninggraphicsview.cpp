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
  \todo appropriate naming for corners and lines would be nice
  */
DekeystoningGraphicsView::DekeystoningGraphicsView(QWidget *parent):
        BaseFilterGraphicsView(parent)
{
    c1 = new Corner(100, 100);
    scene->addItem(c1);

    c2 = new Corner(500, 100);
    scene->addItem(c2);

    c3 = new Corner(500, 500);
    scene->addItem(c3);

    c4 = new Corner(100, 500);
    scene->addItem(c4);

    l1 = new Line(c1, c2);
    l2 = new Line(c2, c3);
    l3 = new Line(c3, c4);
    l4 = new Line(c4, c1);
    scene->addItem(l1);
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);
}

/*! cleen the allocated memory */
DekeystoningGraphicsView::~DekeystoningGraphicsView()
{
    delete c1;
    delete c2;
    delete c3;
    delete c4;
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
    QLineF line1 = QLineF(c1->pos(), c2->pos());
    QLineF line2 = QLineF(c3->pos(), c4->pos());

    qreal width = (line1.length() + line2.length())/2;

    return width;
}

/*! \brief Mean height of the transformation polygon.

  This is used as the height of the resulting Pixmap.
*/
qreal DekeystoningGraphicsView::meanHeight()
{
    QLineF line1 = QLineF(c2->pos(), c3->pos());
    QLineF line2 = QLineF(c1->pos(), c4->pos());

    qreal height = (line1.length() + line2.length())/2;

    return height;
}

/*! \return The polygon as drywed in the scene */
QPolygonF DekeystoningGraphicsView::polygon()
{
    QPolygonF polygon;

    polygon << c1->pos() << c2->pos() << c3->pos() << c4->pos();

    return polygon;
}

/*! Hides the polygon so that it does not interfere with a previewed Pixmap */
void DekeystoningGraphicsView::hidePolygon(bool hide)
{
    bool showPolygon = !hide;

    c1->setVisible(showPolygon);
    c2->setVisible(showPolygon);
    c3->setVisible(showPolygon);
    c4->setVisible(showPolygon);
    l1->setVisible(showPolygon);
    l2->setVisible(showPolygon);
    l3->setVisible(showPolygon);
    l4->setVisible(showPolygon);
}

/** \brief Check if polygon moved since last resetPolygonMoved() */
bool DekeystoningGraphicsView::polygonMoved()
{
    return c1->getCornerMoved()
            || c2->getCornerMoved()
            || c3->getCornerMoved()
            || c4->getCornerMoved();
}

/** \brief Resets all registered moves for the polygon, so that polygonMoved()
returns false */
void DekeystoningGraphicsView::resetPolygonMoved()
{
    c1->resetCornerMoved();
    c2->resetCornerMoved();
    c3->resetCornerMoved();
    c4->resetCornerMoved();
}



