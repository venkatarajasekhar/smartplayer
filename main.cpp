#include "mainwindow.h"
#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDebug>
#include "playlist.h"

bool ifplay = true;

QStringList parse(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QWidget::trUtf8("SmartPlayer Alpha 1"));

    w.show();

    if(argc > 1) {
        w.setPlaylist(parse(argc, argv));
        if(ifplay)
            w.play(0);
    }
    
    return a.exec();
}

QStringList parse(int argc, char *argv[])
{
    QStringList list;

    for(int i = 1; i < argc ; i++) {
        QFileInfo fi(QObject::trUtf8(argv[i]));
        qDebug() << QString(argv[i]);
        if(QString(argv[i]) == QString("-dnp")||QString(argv[i])=="-do-not-play")
            ifplay = false;
        else if(fi.suffix() == "mp3" ||
                fi.suffix() == "wma" ||
                fi.suffix() == "ogg" ||
                fi.suffix() == "MP3" ||
                fi.suffix() == "WMA" ||
                fi.suffix() == "OGG")
            list << argv[i];
        else if(fi.completeSuffix() == "spl")
            list << Playlist(argv[i]).getPathList();
    }

    return list;
}
