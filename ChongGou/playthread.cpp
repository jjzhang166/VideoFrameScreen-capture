#include "playthread.h"

PlayThread::PlayThread(QObject *parent) : QThread(parent)
{
    flag = true;
}
void  PlayThread::run()
{
    while(flag)
    {
        ffmpeg->playLocal();
    }
}
