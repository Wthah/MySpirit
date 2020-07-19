#-------------------------------------------------
#
# Project created by QtCreator 2020-07-11T14:29:02
#
#-------------------------------------------------

QT       += core gui
QT       += sql

CONFIG+=resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySpirit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        myspirit.cpp \
    changewidget.cpp \
    namewidget.cpp \
    storewidget.cpp \
    registerwidget.cpp \
    petwidget.cpp \
    myqlabel.cpp \
    food.cpp \
    ball.cpp \
    brick.cpp \
    paddle.cpp \
    game.cpp \
    gamewindow.cpp

HEADERS  += myspirit.h \
    changewidget.h \
    namewidget.h \
    storewidget.h \
    ../build-MySpirit-Desktop_Qt_5_8_0_MinGW_32bit-Debug/ui_myspirit.h \
    registerwidget.h \
    ../build-MySpirit-Desktop_Qt_5_8_0_MinGW_32bit-Debug/ui_namewidget.h \
    petwidget.h \
    myqlabel.h \
    food.h \
    ball.h \
    brick.h \
    paddle.h \
    game.h \
    gamewindow.h

FORMS    += myspirit.ui \
    changewidget.ui \
    namewidget.ui \
    petwidget.ui \
    storewidget.ui \
    registerwidget.ui \
    food.ui

RC_FILE +=ico.rc

RESOURCES += \
    beijing.qrc \
    chongwu.qrc \
    ico.qrc \
    jiemian.qrc \
    petjiemian.qrc \
    store.qrc

DISTFILES +=
