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
#include <QFileDialog>
#include "playlist/playlist.h"
#include "playlistgenerator/playlistgenerator.h"

void MainWindow::openFolder()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Abrir carpeta..."));
    if(folder.isEmpty())
        return;
    PlaylistGenerator d(folder);
    d.generateFile();
    addFiles(d.getList());
}

void MainWindow::open()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
            tr("Abrir..."), QString(), trUtf8("Todos los archivos soportados (*.mp4 *.wmv *.mp3 *.ogg *.wma *.spl);;"
                                              "Todos los archivos de video (*.mp4 *.wmv);;"
                                              "Todos los archivos de audio (*.mp3 *.ogg *.wma);;"
                                              "Listas de reproducción (*.spl);;"
                                              "Audio MP3 (*.mp3);;"
                                              "Audio OGG (*.ogg);;"
                                              "Audio WMA (*.wma)"));
    if(fileNames.isEmpty())
        return;

    for(int i = 0; i < fileNames.count(); i++) {
        if(!QFileInfo(fileNames[i]).exists())
            continue;
        if(QFileInfo(fileNames[i]).suffix() == "mp3" ||
           QFileInfo(fileNames[i]).suffix() == "wma" ||
           QFileInfo(fileNames[i]).suffix() == "ogg" ||
           QFileInfo(fileNames[i]).suffix() == "MP3" ||
           QFileInfo(fileNames[i]).suffix() == "WMA" ||
           QFileInfo(fileNames[i]).suffix() == "OGG")
            addFile(fileNames[i]);
        else if(QFileInfo(fileNames[i]).completeSuffix() == "spl")
            addFiles(Playlist(fileNames[i]).getPathList());
        else
            addFile(fileNames[i]);
    }
}
