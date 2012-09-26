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
#include "dekeystoningline.h"
#include "dekeystoningcorner.h"

/*! \class DekeystoningLine
    \brief Line of the quadrilateral used to define how to dekeystone

    The lines are updated when the corners are moved. The corners call trackCorners.
  */
DekeystoningLine::DekeystoningLine(DekeystoningCorner *from, DekeystoningCorner *to)
{
    fromCorner = from;
    fromCorner->registerLine(this);
    toCorner = to;
    toCorner->registerLine(this);

    trackCorners();
}

/** \brief redraw the line */
void DekeystoningLine::trackCorners()
{
    setLine(QLineF(fromCorner->scenePos(), toCorner->scenePos()));
}


