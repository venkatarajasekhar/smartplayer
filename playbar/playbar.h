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

#ifndef PLAYBAR_H
#define PLAYBAR_H

#include <QWidget>
#include <QToolButton>
#include <Phonon/SeekSlider>
#include <Phonon/VolumeSlider>
#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>
#include <QLabel>
#include <QDebug>

class Playbar : public QWidget
{
    Q_OBJECT
public:
    explicit Playbar(Phonon::MediaObject *mobject, Phonon::AudioOutput *audio, QWidget *parent = 0);
    QToolButton *bplaypause;
    QToolButton *bstop;
    QToolButton *bback;
    QToolButton *bnext;
    QToolButton *bopen;
    QToolButton *bcreate;
    QLabel *lvolume;
    
signals:
    
public slots:
    void volumechanged(qreal s);
    
private:
    Phonon::SeekSlider *sslider;
    Phonon::VolumeSlider *vslider;
};

#endif // PLAYBAR_H
