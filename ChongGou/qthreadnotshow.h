#ifndef QTHREADNOTSHOW_H
#define QTHREADNOTSHOW_H

#include <QThread>
#include "qffmpegnotshow.h"

class QThreadNotShow: public QThread
{

public:

    void run();
    void setFFmpeg(QFFmpegNotShow *f){ffmpeg = f;}

private:
    QFFmpegNotShow *ffmpeg;
};

#endif // QTHREADNOTSHOW_H
