#include "playlist.h"
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QID3/id3_mp3_frame.h>

Playlist::Playlist(QString file)
{
    get(file);
}

Playlist::Playlist(QStringList files)
{
    get(files);
}

void Playlist::get(QString file)
{
    QFile f(file);
    QStringList l;
    QStringList l2;
    QFileInfo fi(file);
    if(f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        l = QString(f.readAll()).split(QRegExp("\n"));
        f.close();
    }
    for(int d = 0; d < l.count(); d++)
         l2 << (fi.absoluteDir().absoluteFilePath(l[d]));
    list = l2;
}

void Playlist::get(QStringList files)
{
    list = files;
}

QStringList Playlist::getPathList()
{
    return list;
}

QStringList Playlist::getNameList()
{
    QStringList parsedlist;
    for(int i = 0; i < list.count(); i++)
        parsedlist << convert(list[i]);
    return parsedlist;
}

QString Playlist::convert(QString file)
{
    ID3_MP3_Frame frame(file);
    return (frame.getArtist() + " - " + frame.getTitle());
}
