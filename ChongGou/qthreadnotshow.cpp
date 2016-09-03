#include "qthreadnotshow.h"
#include <QDebug>


void  QThreadNotShow::run()
{
//    qDebug() << "明明已经开始run了啊";
    ffmpeg->playLocal();
    delete ffmpeg;
    ffmpeg = Q_NULLPTR;
    delete this;
}
