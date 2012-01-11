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
#ifndef FILTERCONTAINER_H
#define FILTERCONTAINER_H

#include <QTabWidget>
#include <QMap>
#include "basefilter.h"
#include "abstractfilterwidget.h"

class FilterContainer : public QTabWidget
{
    Q_OBJECT
public:
    FilterContainer(QWidget * parent = 0);
    ~FilterContainer();
    void setImage(QPixmap pixmap);
public slots:
    void tabChanged(int index);
private:
    QList<BaseFilter *> tabToFilter;
    int oldIndex; //stores the last selected index

    void updateCurrentTabPixmap(int fromIndex = 1);
};

#endif // FILTERCONTAINER_H
