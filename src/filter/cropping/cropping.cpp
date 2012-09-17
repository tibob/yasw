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
#include "cropping.h"

Cropping::Cropping()
{
    widget = new CroppingWidget();
    filterWidget = widget;
    connect(widget, SIGNAL(rectangleChanged()), this, SLOT(recalculate()));
}

void Cropping::recalculate() {
    QRect rectangle = widget->rectangle();

    outputPixmap = inputPixmap.copy(rectangle);

    widget->setPreview(outputPixmap);
}

/** \brief Returns a universal name for this filter.

 This identifier is unique for the filter. It can be used to identify the
 filter used (for example in configuration files)
 */
QString Cropping::getIdentifier()
{
    return QString("Cropping");
}

/** \brief Returns the localised name of this Filter */
QString Cropping::getName()
{
    return tr("Cropping");
}

AbstractFilterWidget * Cropping::getWidget()
{
    return filterWidget;
}

/** \brief Gets the settings from this filter
*/
QMap<QString, QVariant> Cropping::getSettings()
{
    return widget->getSettings();
}

/** \brief set this filter's settings
 **/
void Cropping::setSettings(QMap<QString, QVariant> settings)
{
    widget->setSettings(settings);
}


