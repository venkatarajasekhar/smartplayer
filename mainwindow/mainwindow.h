/*
 * Copyright (C) 2013, Felipe Cabrera
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTOR ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR ANY OTHER CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Phonon/VideoWidget>
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <QListWidget>
#include "playbar/playbar.h"
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
