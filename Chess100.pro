#-------------------------------------------------
#
# Project created by QtCreator 2024-12-01T22:06:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess100
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

CONFIG += c++11

SOURCES += \
    board_replay.cpp \
        main.cpp \
    board.cpp \
    logic.cpp \
    promotiondialog.cpp \
    savegamedialog.cpp \
    mainwindow.cpp \
    gamewindow.cpp \
    board_widget.cpp \
    db_manager.cpp \
    replay_list_games_window.cpp

HEADERS += \
    board.h \
    board_replay.h \
    men.h \
    logic.h \
    status.h \
    promotiondialog.h \
    savegamedialog.h \
    mainwindow.h \
    gamewindow.h \
    board_widget.h \
    db_manager.h \
    replay_list_games_window.h

FORMS += \
    promotiondialog.ui \
    savegamedialog.ui \
    mainwindow.ui \
    gamewindow.ui \
    replay_list_games_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Chess100.pro

DISTFILES += \
    Chess100.pro.user

RESOURCES += \
    res.qrc
