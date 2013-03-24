#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>

class Playlist
{
    Q_GADGET
public:
    Playlist(QString file = QString());
    Playlist(QStringList files = QStringList());
    void get(QString file);
    void get(QStringList files);
    QStringList getPathList();
    QStringList getNameList();
    static QString convert(QString file);

protected:
    QStringList list;
};

#endif // PLAYLIST_H
