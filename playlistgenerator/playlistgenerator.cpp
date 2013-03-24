#include "playlistgenerator.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

PlaylistGenerator::PlaylistGenerator(QString dir)
{
    dirpath = dir;
    generate();
}

void PlaylistGenerator::generate()
{
    QDir d(dirpath);
    QStringList l = d.entryList();

    for(int i = 0; i < l.count(); i++) {
        if(l[i] == "." || l[i] == "..")
            continue;
        if(QFileInfo(l[i]).suffix() == "mp3" ||
           QFileInfo(l[i]).suffix() == "ogg" ||
           QFileInfo(l[i]).suffix() == "wma" ||
           QFileInfo(l[i]).suffix() == "MP3" ||
           QFileInfo(l[i]).suffix() == "OGG" ||
           QFileInfo(l[i]).suffix() == "WMA")
            list << l[i];
    }
}

QString PlaylistGenerator::generatePlaylist()
{
    return list.join("\r\n");
}

void PlaylistGenerator::generateFile()
{
    QFile data(dirpath + QString("/playlist.spl"));
    if(data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << generatePlaylist();
    }
}

QStringList PlaylistGenerator::getList()
{
    QStringList s;
    for(int i = 0; i < list.count(); i++)
        s << (dirpath + "/" + list[i]);
    return s;
}
