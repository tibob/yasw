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
#ifndef BASEFILTERWIDGET_H
#define BASEFILTERWIDGET_H

#include <QWidget>
#include "abstractfilterwidget.h"

namespace Ui {
    class BaseFilterWidget;
}

class BaseFilterWidget : public AbstractFilterWidget {
    Q_OBJECT
public:
    BaseFilterWidget(QWidget *parent = 0);
    ~BaseFilterWidget();
    void setPixmap(QPixmap pixmap);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::BaseFilterWidget *ui;
};

#endif // BASEFILTERWIDGET_H
