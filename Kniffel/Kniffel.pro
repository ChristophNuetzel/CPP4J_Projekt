#-------------------------------------------------
#
# Project created by QtCreator 2013-01-28T16:47:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kniffel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pointcalculator.cpp \
    calculatortestprogram.cpp

HEADERS  += mainwindow.h \
    pointcalculator.h \
    calculatortestprogram.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
