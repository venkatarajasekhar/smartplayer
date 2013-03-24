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
