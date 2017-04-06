#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T02:41:04
#
#-------------------------------------------------

include ( ../3rdparty/QsLog/QsLog.pri )

QT += core gui

QT += network widgets

CONFIG += console

QT -= gui

QT += qml quick

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

TARGET = dracula
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ./GUI/
INCLUDEPATH += ./Logic/

SOURCES += \
    Logic/gamestate.cpp \
    Logic/lord.cpp \
    Logic/player.cpp \
    main.cpp \
    Logic/doctor.cpp \
    Logic/hunter.cpp \
    Logic/helsing.cpp \
    Logic/mina.cpp \
    Logic/dracula.cpp \
    gamemanager.cpp \
    loader.cpp \
    GUI/guimanager.cpp

HEADERS += \
    constants.h \
    Logic/gamestate.h \
    Logic/lord.h \
    Logic/player.h \
    Logic/doctor.h \
    Logic/hunter.h \
    Logic/helsing.h \
    Logic/mina.h \
    Logic/dracula.h \
    Logic/logicobjects.h \
    gamemanager.h \
    loader.h \
    GUI/guimanager.h
