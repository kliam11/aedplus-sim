#ifndef HEARTDISPLAY_H
#define HEARTDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QMovie>

/**
 * @brief Custom widget to display patient heart rhythm signal
 *
 * @param a parent widget
 *
 */

class HeartDisplay: public QWidget
{
    Q_OBJECT

public:
    HeartDisplay(QWidget *parent = nullptr);
    ~HeartDisplay();
    void changeRhythm(int cond);

private:
    int curRhytm;
    QMovie *gifs[4];
    QLabel *label;

signals:
    void signal();

public slots:
    void slot();

};

#endif // HEARTDISPLAY_H
