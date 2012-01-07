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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rotation.h"

Rotation::Rotation(QObject * parent) : BaseFilter(parent)
{
    widget = new RotationWidget();
    filterWidget = widget;
    connect(widget, SIGNAL(rotationChanged()), this, SLOT(recalculate()));
}

QString Rotation::getName()
{
    return QString("Rotation");
}

AbstractFilterWidget * Rotation::getWidget()
{
    return widget;
}

void Rotation::recalculate()
{
    rotationMatrix.reset();
    rotationMatrix.rotate(widget->rotation());
    outputPixmap = inputPixmap.transformed(rotationMatrix);
    widget->setPreview(outputPixmap);
}

///*! \fixme implement this */
//QPixmap Rotation::getFilteredImage()
//{
//    return inputPixmap;
//}
