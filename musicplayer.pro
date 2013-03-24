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
           mainwindow.cpp \
           playbar.cpp \
           qtwin.cpp \
    playlistgenerator.cpp \
    playlist.cpp

HEADERS  += mainwindow.h \
            playbar.h \
            qtwin.h \
    playlistgenerator.h \
    playlist.h \
    version.h

RESOURCES += \
    icons.qrc

OTHER_FILES += \
    musicplayer.rc \
    COPYING
