#include "HeartDisplay.h"

HeartDisplay::HeartDisplay(QWidget *parent): QWidget(parent), curRhytm(0)
{
    gifs[0] = new QMovie(":/gifs/rsc/gif/PEA_RHYTHM.gif");
    gifs[1] = new QMovie(":/gifs/rsc/gif/Asystole_RHYTHM.gif");
    gifs[2] = new QMovie(":/gifs/rsc/gif/VF_heartRhythm.gif");
    gifs[3] = new QMovie(":/gifs/rsc/gif/VT_heartRhythm.gif");
    label = new QLabel(this);

    QObject::connect(this, &HeartDisplay::signal, this, &HeartDisplay::slot);

    slot();
}

HeartDisplay::~HeartDisplay()
{
    for(int i=0; i<4; ++i) {
        delete gifs[i];
    }
    delete label;
}

void HeartDisplay::slot()
{
    if(label->movie()) label->movie()->stop();
    label->setMovie(gifs[curRhytm]);
    gifs[curRhytm]->start();
}

void HeartDisplay::changeRhythm(int cond)
{
    if (cond == -1) {
        label->hide();
    }
    else if (cond>=0 && cond<4) {
        label->show();
        curRhytm = cond;
        emit signal();
    }
}
