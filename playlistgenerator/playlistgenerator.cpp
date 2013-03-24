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

#include "playlistgenerator.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

PlaylistGenerator::PlaylistGenerator(QString dir)
{
    dirpath = dir;
    generate();
}

void PlaylistGenerator::generate()
{
    QDir d(dirpath);
    QStringList l = d.entryList();

    for(int i = 0; i < l.count(); i++) {
        if(l[i] == "." || l[i] == "..")
            continue;
        if(QFileInfo(l[i]).suffix() == "mp3" ||
           QFileInfo(l[i]).suffix() == "ogg" ||
           QFileInfo(l[i]).suffix() == "wma" ||
           QFileInfo(l[i]).suffix() == "MP3" ||
           QFileInfo(l[i]).suffix() == "OGG" ||
           QFileInfo(l[i]).suffix() == "WMA")
            list << l[i];
    }
}

QString PlaylistGenerator::generatePlaylist()
{
    return list.join("\r\n");
}

void PlaylistGenerator::generateFile()
{
    QFile data(dirpath + QString("/playlist.spl"));
    if(data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << generatePlaylist();
    }
}

QStringList PlaylistGenerator::getList()
{
    QStringList s;
    for(int i = 0; i < list.count(); i++)
        s << (dirpath + "/" + list[i]);
    return s;
}
