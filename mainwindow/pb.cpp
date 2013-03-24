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

void MainWindow::playpause()
{
    if(playing) {
        media->pause();
        playing = false;
        stopped = false;
        paused = true;
        pb->bplaypause->setIcon(QIcon(":/icons/1359894943_playback_pause.png"));
    }
    else if(stopped) {
        play();
    }
    else if(paused) {
        media->play();
        playing = true;
        stopped = false;
        paused = false;
        pb->bplaypause->setIcon(QIcon(":/icons/1359894848_playback_play.png"));
    }
    listwidget->setCurrentRow(count);
}

void MainWindow::stop()
{
    media->stop();
    playing = false;
    stopped = true;
    paused = false;
    vwidget->hide();
    listwidget->show();
    pb->bplaypause->setIcon(QIcon(":/icons/1359894848_playback_play.png"));
}

void MainWindow::next()
{
    if((count+1) >= list.count())
        return;
    play(++count);
    listwidget->setCurrentRow(count);
}

void MainWindow::back()
{
    if(count <= 0)
        return;
    play(--count);
    listwidget->setCurrentRow(count);
}
