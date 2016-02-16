#-------------------------------------------------
#
# Project created by QtCreator 2016-02-12T12:46:28
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = audio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dtmfgenerator.cpp

HEADERS  += mainwindow.h \
    dtmfgenerator.h

FORMS    += mainwindow.ui
