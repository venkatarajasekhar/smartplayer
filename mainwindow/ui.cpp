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

#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFileInfo>

void MainWindow::Make()
{
    setWindowIcon(mainIcon());

    media = new Phonon::MediaObject;
    audio = new Phonon::AudioOutput;
    vwidget = new Phonon::VideoWidget;
    pb = new Playbar(media, audio);
    listwidget = new QListWidget;

    vwidget->hide();

    vwidget->setMinimumSize(380, 285);
    listwidget->setMinimumSize(380, 285);

    Phonon::createPath(media, audio);
    Phonon::createPath(media, vwidget);

    setCentralWidget(new QWidget);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(vwidget);
    layout2->addWidget(listwidget);
    layout2->setMargin(0);

    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->setMargin(0);
    layout1->addLayout(layout2);
    layout1->addWidget(pb);

    centralWidget()->setLayout(layout1);

    connect(media, SIGNAL(aboutToFinish()), this, SLOT(enqueue()));
    connect(pb->bplaypause, SIGNAL(clicked()), this, SLOT(playpause()));
    connect(pb->bstop, SIGNAL(clicked()), this, SLOT(stop()));
    connect(pb->bnext, SIGNAL(clicked()), this, SLOT(next()));
    connect(pb->bback, SIGNAL(clicked()), this, SLOT(back()));
    connect(pb->bopen, SIGNAL(clicked()), this, SLOT(open()));
    connect(pb->bcreate, SIGNAL(clicked()), this, SLOT(openFolder()));
    connect(listwidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playlistClicked(QModelIndex)));
    connect(media, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(pN()));
}

void MainWindow::hideandshow(QString path)
{
    if(QFileInfo(path).completeSuffix()=="mp3"||
       QFileInfo(path).completeSuffix()=="wma"||
       QFileInfo(path).completeSuffix()=="mid"||
       QFileInfo(path).completeSuffix()=="ogg")
    {
        vwidget->hide();
        listwidget->show();
    }
    else if(QFileInfo(path).completeSuffix()=="mp4"||
            QFileInfo(path).completeSuffix()=="wmv"||
            QFileInfo(path).completeSuffix()=="avi"||
            QFileInfo(path).completeSuffix()=="MP4"||
            QFileInfo(path).completeSuffix()=="WMV"||
            QFileInfo(path).completeSuffix()=="AVI")
    {
        listwidget->hide();
        vwidget->show();
    }
}

void MainWindow::pN()
{
    listwidget->setCurrentRow(count);
}
