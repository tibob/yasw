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
#ifndef ROTATION_H
#define ROTATION_H

#include <QObject>
#include <QWidget>
#include "rotationwidget.h"
#include "basefilter.h"

class Rotation: public BaseFilter
{
    Q_OBJECT
public:
    Rotation(QObject * parent = 0);
    AbstractFilterWidget* getWidget();
    QString getName();
    QMap<QString, QVariant> getSettings();
    void setSettings(QMap <QString, QVariant> settings);

public slots:
    void recalculate();

private:
    RotationWidget *widget;
    QTransform rotationMatrix;
};

#endif // ROTATION_H
