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
#ifndef ABSTRACTFILTERWIDGET_H
#define ABSTRACTFILTERWIDGET_H

#include <QWidget>

class AbstractFilterWidget : public QWidget
{
public:
    AbstractFilterWidget(QWidget *parent = 0);
    //! \brief Sets the input pixmap
    virtual void setPixmap(QPixmap pixmap);
    //! \brief Sets the filtered pixmap for preview */
    virtual void setPreview(QPixmap pixmap);
protected:
    QPixmap inputPixmap;
    QPixmap previewPixmap;
};

#endif // ABSTRACTFILTERWIDGET_H
