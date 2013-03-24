#-------------------------------------------------
#
# Project created by QtCreator 2013-01-23T11:50:05
#
#-------------------------------------------------

QT       += core gui phonon

LIBS += -L../qid3/release -lqid3

win32:RC_FILE = musicplayer.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smartplayer
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow/mainwindow.cpp \
           playbar/playbar.cpp \
           qtwin/qtwin.cpp \
           playlistgenerator/playlistgenerator.cpp \
           playlist/playlist.cpp \
    mainwindow/class.cpp \
    mainwindow/ui.cpp \
    mainwindow/open.cpp \
    mainwindow/play.cpp \
    mainwindow/pb.cpp

HEADERS  += mainwindow/mainwindow.h \
            playbar/playbar.h \
            qtwin/qtwin.h \
            playlistgenerator/playlistgenerator.h \
            playlist/playlist.h \
            version.h

RESOURCES += \
    icons.qrc

OTHER_FILES += \
    musicplayer.rc \
    COPYING \
    README.md
