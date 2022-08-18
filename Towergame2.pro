#-------------------------------------------------
#
# Project created by QtCreator 2019-06-01T20:47:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Towergame2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mainwindow2.cpp \
    start.cpp \
    one.cpp \
    waypoint.cpp \
    towerposition.cpp \
    towerfreeze.cpp \
    tower.cpp \
    towermagic.cpp \
    ice.cpp \
    bullet.cpp \
    ray.cpp \
    enemy.cpp \
    player.cpp \
    poison.cpp \
    gold.cpp \
    introdution.cpp \
    replay.cpp


HEADERS += \
        mainwindow.h \
    mainwindow2.h \
    start.h \
    one.h \
    waypoint.h \
    towerposition.h \
    towerfreeze.h \
    tower.h \
    towermagic.h \
    ice.h \
    bullet.h \
    ray.h \
    enemy.h \
    player.h \
    poison.h \
    gold.h \
    introdution.h \
    replay.h

FORMS += \
        mainwindow.ui \
    mainwindow2.ui \
    start.ui \
    one.ui \
    introdution.ui \
    replay.ui

RESOURCES += \
    picture.qrc \
    picture.qrc

DISTFILES +=
