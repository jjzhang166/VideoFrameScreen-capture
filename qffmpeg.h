#ifndef QFFMPEG_H
#define QFFMPEG_H

//必须加以下内容,否则编译不能通过,为了兼容C和C99标准
#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif

//引入ffmpeg头文件
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
}

#include <QObject>
#include <QMutex>
#include <QImage>
#include <pictureutils.h>

class QFFmpeg : public QObject
{
    Q_OBJECT
public:
    explicit QFFmpeg(QObject *parent = 0);
    ~QFFmpeg();

    enum State//表示播放状态的值
    {
        PlayingState,
        PausedState,
        StoppedState//界面啥都没有，播放完了
    };

    bool Init();
    State getState(){return currentState;}
    void SetUrl(QString url){this->url=url;}
    QString Url()const{return url;}
    int VideoWidth()const{return videoWidth;}
    int VideoHeight()const{return videoHeight;}
    bool getPlaying(){return playing;}
    void setPlaying(bool p){playing = p;}
    void setPause(bool b){neededPause = b;}
    void setSeekAndSeekTime(bool s,qint64 t){neededSeek = s;seekTime = t;}//先将neededSeek设置成true才能调用seek方法
    QString getPath(){return savePath;}
    void seek();

    qint64 getCurrentTime(){return currentTime;}
    qint64 getTotalTime(){return totalTime;}


protected:
//    QMutex mutex;
    AVPicture  pAVPicture;
    AVFormatContext *pAVFormatContext;
    AVCodecContext *pAVCodecContext;
    AVFrame *pAVFrame;
    SwsContext * pSwsContext;
    AVPacket pAVPacket;

    QString url;
    QString savePath;
    int videoWidth;
    int videoHeight;
    int videoStreamIndex;
    bool playing;
    bool isInit;
    bool neededPause;
    bool neededSeek;
    State currentState;
    qint64 currentTime;
    qint64 totalTime;
    qint64 seekTime;
    qint64 startPts;

signals:
    void GetImage(const QImage &image);
    void sendSavePath(const QString savePath);
    void updateTime(const qint64 time);

public slots:
    void getSavePath(const QString s);
    virtual void playLocal();
};

#endif // QFFMPEG_H
