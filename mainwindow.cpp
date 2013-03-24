#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>
#include <QID3/id3_mp3_frame.h>
#include "playlist.h"
#include "playlistgenerator.h"
#include "qtwin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
#ifdef Q_WS_WIN
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(this);
        this->setContentsMargins(0, 0, 0, 0);
    }
#endif
    playing = false;
    stopped = true;
    paused = false;
    Make();
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

MainWindow::~MainWindow()
{
    
}

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

void MainWindow::pN()
{
    listwidget->setCurrentRow(count);
}

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

void MainWindow::play(QString path)
{
    hideandshow(path);
    media->setCurrentSource(Phonon::MediaSource(path));
    media->play();
    playing = true;
    paused = false;
    stopped = false;
    pb->bplaypause->setIcon(QIcon(":/icons/1359894848_playback_play.png"));
    listwidget->setCurrentRow(count);
}

void MainWindow::play()
{
    if(list.count()==0)
        return;
    hideandshow(list[count]);
    media->setCurrentSource(Phonon::MediaSource(list[count]));
    media->play();
    playing = true;
    paused = false;
    stopped = false;
    pb->bplaypause->setIcon(QIcon(":/icons/1359894848_playback_play.png"));
    listwidget->setCurrentRow(count);
}

void MainWindow::play(int i)
{
    if(list.count()<=i)
        return;
    hideandshow(list[count = i]);
    media->setCurrentSource(Phonon::MediaSource(list[i]));
    media->play();
    playing = true;
    paused = false;
    stopped = false;
    pb->bplaypause->setIcon(QIcon(":/icons/1359894848_playback_play.png"));
    listwidget->setCurrentRow(count);
}

void MainWindow::addFile(QString path)
{
    list.append(path);
    listwidget->addItem(Playlist::convert(path));
}

void MainWindow::addFiles(QStringList files)
{
    list = list + files;
    listwidget->addItems(Playlist(files).getNameList());
}

void MainWindow::setPlaylist(QStringList files)
{
    count = 0;
    list = files;
    listwidget->clear();
    listwidget->addItems(Playlist(files).getNameList());
}

void MainWindow::enqueue()
{
    count++;
    if(count >= list.count())
        count = 0;
    else
        media->enqueue(Phonon::MediaSource(list[count]));
}

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

void MainWindow::playlistClicked(QModelIndex model)
{
    play(model.row());
}
