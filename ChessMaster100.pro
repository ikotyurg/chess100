QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    board_replay.cpp \
    board_widget.cpp \
    db_manager.cpp \
    logic.cpp \
    main.cpp \
    mainwindow.cpp \
    promotiondialog.cpp \
    replay_list_games_window.cpp \
    savegamedialog.cpp

HEADERS += \
    board.h \
    board_replay.h \
    board_widget.h \
    db_manager.h \
    logic.h \
    mainwindow.h \
    men.h \
    promotiondialog.h \
    replay_list_games_window.h \
    savegamedialog.h \
    status.h

FORMS += \
    mainwindow.ui \
    promotiondialog.ui \
    replay_list_games_window.ui \
    savegamedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc
