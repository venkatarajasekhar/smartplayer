#ifndef PLAYLISTGENERATOR_H
#define PLAYLISTGENERATOR_H

#include <QWidget>

class PlaylistGenerator
{
    Q_GADGET
public:
    PlaylistGenerator(QString dir = QString());
    void generate();
    QString generatePlaylist();
    void generateFile();
    QStringList getList();

protected:
    QString dirpath;
    QStringList list;

};

#endif // PLAYLISTGENERATOR_H
