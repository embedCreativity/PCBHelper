#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T01:53:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PCBHelper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlite3.c

HEADERS  += mainwindow.h \
    sqlite3.h \
    sqlite3ext.h

FORMS    += mainwindow.ui

# Icon file reference
RC_FILE = myapp.rc
