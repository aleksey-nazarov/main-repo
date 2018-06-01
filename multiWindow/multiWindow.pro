#-------------------------------------------------
#
# Project created by QtCreator 2018-06-01T18:40:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multiWindow
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    sidewindow.cpp \
    sidedialog.cpp

HEADERS  += widget.h \
    sidewindow.h \
    sidedialog.h

FORMS    += widget.ui \
    sidewindow.ui \
    sidedialog.ui
