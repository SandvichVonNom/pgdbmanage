#-------------------------------------------------
#
# Project created by QtCreator 2015-01-17T17:27:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PGDBManage
TEMPLATE = app
QMAKE_CXXFLAGS += -lexpect5.45 -ltcl8.6

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES +=


unix:!macx: LIBS += -L/usr/local/lib/ \
                    -L/usr/local/lib/expect5.45/ -lexpect5.45 \
                    -L/usr/local/lib64/ -ltcl8.6

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
