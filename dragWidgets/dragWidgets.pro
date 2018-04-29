#-------------------------------------------------
#
# Project created by QtCreator 2018-04-25T17:24:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dragWidgets
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    miniwidget.cpp \
    containerwidget.cpp

HEADERS  += widget.h \
    miniwidget.h \
    containerwidget.h

FORMS    += widget.ui \
    miniwidget.ui \
    containerwidget.ui
