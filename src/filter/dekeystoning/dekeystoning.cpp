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
#include "dekeystoning.h"
#include <QDebug>
#include <QColor>

Dekeystoning::Dekeystoning(QObject *parent)
{
    widget = new DekeystoningWidget();
    filterWidget = widget;
    connect(widget, SIGNAL(polygonChanged()), this, SLOT(recalculate()));


    if (parent) {
        /* Connect slots to the filtercontainer */
        connect(parent, SIGNAL(selectionColorChanged(QColor)), widget, SLOT(setSelectionColor(QColor)));
    }
}

/** \brief Returns a universal name for this filter.

 This identifier is unique for the filter. It can be used to identify the
 filter used (for example in configuration files)
 */
QString Dekeystoning::getIdentifier()
{
    return QString("Dekeystoning");
}

/*! \brief Retruns the localised name of the filter */
QString Dekeystoning::getName()
{
    return tr("Dekeystoning");
}

/** \brief Gets the settings from this filter
*/
QMap<QString, QVariant> Dekeystoning::getSettings()
{
    return widget->getSettings();
}

/** \brief set this filter's settings
 **/
void Dekeystoning::setSettings(QMap<QString, QVariant> settings)
{
    widget->setSettings(settings);
}

// NOTE: cannot this be handled by BaseFilter::getWidget() ?
AbstractFilterWidget* Dekeystoning::getWidget()
{
    return widget;
}

void Dekeystoning::recalculate()
{
    QPolygonF polygon = widget->polygon();

    QTransform transformMatrix;
    /* it might not be possbible to calculate a treansformation matrix */
    if (!QTransform::quadToSquare(polygon, transformMatrix)) {
        qDebug() << "No transformation exists for this";
        return;
    }

    qreal width  = widget->meanWidth();
    qreal height = widget->meanHeight();
    QTransform scaleMatrix = QTransform::fromScale(width, height);

    QTransform transformationMatrix = transformMatrix * scaleMatrix;

    outputPixmap = inputPixmap.transformed(transformationMatrix);

    widget->setPreview(outputPixmap);
}

