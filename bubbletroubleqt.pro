#-------------------------------------------------
#
# Project created by QtCreator 2017-02-02T19:51:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bubbletroubleqt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    bubbletrouble.cpp \
    bubble.cpp \
    shot.cpp \
    haste.cpp \
    invincibility.cpp \
    gold.cpp \
    powerup.cpp \
    itembt.cpp \
    silver.cpp \
    secret.cpp \
    detonator.cpp

HEADERS  += mainwindow.h \
    player.h \
    bubbletrouble.h \
    bubble.h \
    shot.h \
    haste.h \
    invincibility.h \
    gold.h \
    powerup.h \
    itembt.h \
    silver.h \
    secret.h \
    detonator.h

FORMS    += mainwindow.ui
