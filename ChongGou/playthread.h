#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>
#include "qffmpeg.h"
#include <QTimer>

class PlayThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayThread(QObject *parent = 0);

    void run();
    void setffmpeg(QFFmpeg *f){ffmpeg=f;}
    QFFmpeg *getFFmpeg(){return ffmpeg;}

    void setFlag(bool f){flag = f;}

private:
    QFFmpeg *ffmpeg;
    bool flag;

signals:

public slots:
};

#endif // PLAYTHREAD_H
