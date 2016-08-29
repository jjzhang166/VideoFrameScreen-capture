#ifndef QFFMPEGNOTSHOW_H
#define QFFMPEGNOTSHOW_H

#include <QObject>
#include "qffmpeg.h"

class QFFmpegNotShow : public QFFmpeg
{
    Q_OBJECT
public:
     QFFmpegNotShow();
     void setStartTime(qint64 t){startTime = t;}
     void setEndTime(qint64 t){endTime = t;}
     void setSaveType(int t){type = t;}
signals:

public slots:
     void playLocal();

private:
     qint64 startTime;
     qint64 endTime;
     int type;


};

#endif // QFFMPEGNOTSHOW_H
