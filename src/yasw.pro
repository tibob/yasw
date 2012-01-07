# Copyright (C) 2012 Robert Chéramy (robert@cheramy.net)
# 
# This file is part of YASW (Yet Another Scan Wizard).
# 
# YASW is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# YASW is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

TARGET = yasw
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    filter/dekeystoning/corner.cpp \
    filter/dekeystoning/line.cpp \
    filter/basefilter.cpp \
    filter/basefiltergraphicsview.cpp \
    filter/basefilterwidget.cpp \
    filtercontainer.cpp \
    filter/dekeystoning/dekeystoningwidget.cpp \
    filter/dekeystoning/dekeystoninggraphicsview.cpp \
    filter/dekeystoning/dekeystoning.cpp \
    filter/rotation/rotationwidget.cpp \
    filter/rotation/rotation.cpp \
    filter/abstractfilterwidget.cpp
HEADERS += mainwindow.h \
    filter/dekeystoning/corner.h \
    filter/dekeystoning/line.h \
    filter/basefilter.h \
    filter/basefiltergraphicsview.h \
    filter/basefilterwidget.h \
    filtercontainer.h \
    filter/dekeystoning/dekeystoningwidget.h \
    filter/dekeystoning/dekeystoninggraphicsview.h \
    filter/dekeystoning/dekeystoning.h \
    filter/rotation/rotationwidget.h \
    filter/rotation/rotation.h \
    filter/abstractfilterwidget.h
FORMS += mainwindow.ui \
    filter/basefilterwidget.ui \
    filter/dekeystoning/dekeystoningwidget.ui \
    filter/rotation/rotationwidget.ui
INCLUDEPATH += filter \
    filter/dekeystoning \
    filter/rotation
RESOURCES += icons/icons.qrc

OTHER_FILES += \
    ../documentation/doxygen-mainpage.txt
