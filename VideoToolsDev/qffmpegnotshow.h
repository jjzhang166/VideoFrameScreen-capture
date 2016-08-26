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

signals:

public slots:
     void playLocal();
     void setSaveType(int type){saveType = type;}
private:
     qint64 startTime;
     qint64 endTime;
     int saveType;
};

#endif // QFFMPEGNOTSHOW_H
