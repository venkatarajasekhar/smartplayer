#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Phonon/VideoWidget>
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <QListWidget>
#include "playbar.h"
#include <QIcon>

static QIcon mainIcon()
{
    QIcon s;
    s.addFile(":/icons/1363519519_headphones.png", QSize(16, 16));
    s.addFile(":/icons/1363519518_headphones.png", QSize(32, 32));
    s.addFile(":/icons/1363519515_headphones.png", QSize(48, 48));
    return s;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Make();

public slots:
    void play(QString path);
    void play();
    void play(int i);
    void addFile(QString path);
    void addFiles(QStringList files);
    void setPlaylist(QStringList files);
    void enqueue();
    void playpause();
    void stop();
    void next();
    void back();
    void playlistClicked(QModelIndex model);
    void open();
    void openFolder();
    void pN();

private:
    bool playing;
    bool paused;
    bool stopped;
    void hideandshow(QString path);
    Playbar *pb;
    Phonon::MediaObject *media;
    Phonon::VideoWidget *vwidget;
    Phonon::AudioOutput *audio;
    QListWidget *listwidget;
    QStringList list;
    int count;
};

#endif // MAINWINDOW_H
