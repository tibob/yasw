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
#ifndef DEKEYSTONINGGRAPHICSVIEW_H
#define DEKEYSTONINGGRAPHICSVIEW_H

#include <QPoint>
#include "basefiltergraphicsview.h"
#include "dekeystoningcorner.h"
#include "dekeystoningline.h"

class DekeystoningGraphicsView : public BaseFilterGraphicsView
{
    Q_OBJECT
public:
    DekeystoningGraphicsView(QWidget *parent);
    ~DekeystoningGraphicsView();
    qreal meanWidth();
    qreal meanHeight();
    QPolygonF polygon();
    bool polygonMoved();
    void resetPolygonMoved();
    QMap<QString, QVariant> getSettings();
    void setSettings(QMap <QString, QVariant> settings);
public slots:
    void hidePolygon(bool hide);

private:
    DekeystoningCorner *topLeftCorner,
            *topRightCorner,
            *bottomRightCorner,
            *bottomLeftCorner;
    DekeystoningLine *l1, *l2, *l3, *l4;
    // predefined corner positions for default settings
    const QPoint defaultTopLeft = QPoint(100, 100);
    const QPoint defaultTopRight = QPoint(500, 100);
    const QPoint defaultBottomLeft = QPoint(100, 500);
    const QPoint defaultBottomRight = QPoint(500, 500);
};

#endif // DEKEYSTONINGGRAPHICSVIEW_H
