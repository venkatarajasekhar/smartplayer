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
