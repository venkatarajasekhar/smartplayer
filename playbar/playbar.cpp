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

#include "playbar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSize>
#include <QIcon>

Playbar::Playbar(Phonon::MediaObject *mobject, Phonon::AudioOutput *audio, QWidget *parent) :
    QWidget(parent)
{
    sslider = new Phonon::SeekSlider;
    vslider = new Phonon::VolumeSlider;
    bplaypause = new QToolButton;
    bstop = new QToolButton;
    bback = new QToolButton;
    bnext = new QToolButton;
    bopen = new QToolButton;
    bcreate = new QToolButton;
    lvolume = new QLabel;

    bplaypause->setToolTip(tr("Reproducir/Pausar"));
    bstop->setToolTip(tr("Detener"));
    bback->setToolTip(tr("Rebobinar"));
    bnext->setToolTip(tr("Adelantar"));
    bopen->setToolTip(trUtf8("Añadir archivos..."));
    bcreate->setToolTip(tr("Abrir carpeta..."));

    bplaypause->setIcon(QIcon(":/icons/1359894848_playback_play.png"));
    bstop->setIcon(QIcon(":/icons/1359894939_playback_stop.png"));
    bback->setIcon(QIcon(":/icons/1359895090_playback_rew.png"));
    bnext->setIcon(QIcon(":/icons/1359895096_playback_ff.png"));
    bopen->setIcon(QIcon(":/icons/1363513956_folder_open.png"));
    bcreate->setIcon(QIcon(":/icons/1364111382_folder_plus.png"));

    vslider->setAudioOutput(audio);
    vslider->setMaximumWidth(100);

    sslider->setMediaObject(mobject);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->setMargin(0);
    layout2->addWidget(bplaypause);
    layout2->addWidget(bstop);
    layout2->addWidget(bback);
    layout2->addWidget(bnext);
    layout2->addWidget(bopen);
    layout2->addWidget(bcreate);
    layout2->addStretch();
    layout2->addWidget(lvolume);
    layout2->addWidget(vslider);

    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(sslider);
    layout1->addLayout(layout2);

    setLayout(layout1);
    setMaximumHeight(70);
    connect(audio, SIGNAL(volumeChanged(qreal)), this, SLOT(volumechanged(qreal)));
    volumechanged(audio->volume());
}

void Playbar::volumechanged(qreal s)
{
    lvolume->setText(QString::number(s*100) + "%");
}
