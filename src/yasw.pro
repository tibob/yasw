# -------------------------------------------------
# Project created by QtCreator 2011-12-23T22:19:19
# -------------------------------------------------
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
