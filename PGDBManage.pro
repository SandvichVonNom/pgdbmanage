#-------------------------------------------------
#
# Project created by QtCreator 2015-01-17T17:27:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PGDBManage
TEMPLATE = app
QMAKE_CXXFLAGS += --no-as-needed -lexpect -ltcl 8.6

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES +=


unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/ -lexpect

INCLUDEPATH += $$PWD/../../../../usr/include/tcl8.6
DEPENDPATH += $$PWD/../../../../usr/include/tcl8.6
