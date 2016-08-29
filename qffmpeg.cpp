#include "qffmpeg.h"
#include "helper.h"
#include <QDateTime>
#include <QDebug>
#include <QTime>
#include <QThread>

QFFmpeg::QFFmpeg(QObject *parent) :
    QObject(parent)
{
    videoStreamIndex=-1;
    av_register_all();//注册库中所有可用的文件格式和解码器
    avformat_network_init();//初始化网络流格式,使用RTSP网络流时必须先执行
    pAVFormatContext = avformat_alloc_context();//申请一个AVFormatContext结构的内存,并进行简单初始化
    pAVFrame=av_frame_alloc();
    playing = false;
    isInit = false;
    neededPause = false;
    neededSeek = false;
    startPts =  -1;
    currentTime = 0;
    totalTime = 0;
}

QFFmpeg::~QFFmpeg()
{
    avformat_free_context(pAVFormatContext);
    av_frame_free(&pAVFrame);
    if(isInit)
    {
        sws_freeContext(pSwsContext);
    }
}

bool QFFmpeg::Init()
{
    //打开视频流
    int result=avformat_open_input(&pAVFormatContext, url.toStdString().c_str(),NULL,NULL);
    if (result<0){
        qDebug()<<url<<endl;
        qDebug()<<"打开视频流失败";
        return false;
    }

    //获取视频流信息
    result=avformat_find_stream_info(pAVFormatContext,NULL);
    if (result<0){
        qDebug()<<"获取视频流信息失败";
        return false;
    }

    //获取视频流索引
    videoStreamIndex = -1;
    for (uint i = 0; i < pAVFormatContext->nb_streams; i++) {
        if (pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex==-1){
        qDebug()<<"获取视频流索引失败";
        return false;
    }

    //获取视频流的分辨率大小
    pAVCodecContext = pAVFormatContext->streams[videoStreamIndex]->codec;
    videoWidth=pAVCodecContext->width;
    videoHeight=pAVCodecContext->height;

    avpicture_alloc(&pAVPicture,PIX_FMT_RGB24,videoWidth,videoHeight);

    AVCodec *pAVCodec;

    //获取视频流解码器
    pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
    pSwsContext = sws_getContext(videoWidth,videoHeight,PIX_FMT_YUV420P,videoWidth,videoHeight,PIX_FMT_RGB24,SWS_BICUBIC,0,0,0);

    //打开对应解码器
    result=avcodec_open2(pAVCodecContext,pAVCodec,NULL);
    if (result<0){
        qDebug()<<"打开解码器失败";
        return false;
    }

    qDebug()<<"初始化视频流成功";
    playing = true;
    isInit = true;
    return true;
}

void QFFmpeg::seek()
{
    int target= av_rescale_q(seekTime,av_get_time_base_q(),pAVFormatContext->streams[videoStreamIndex]->time_base);
    av_seek_frame(pAVFormatContext,videoStreamIndex,target+startPts,AVSEEK_FLAG_FRAME); //AV_TIME_BASE
}

void QFFmpeg::playLocal()
{
    //一帧一帧读取视频
//    av_read_frame(pAVFormatContext, &pAVPacket);
    totalTime = pAVFormatContext->duration;

    PictureUtils p;
    if (savePath.isEmpty())
    {
        qDebug() << "传过来的保存路径是空";
    }
    else
    {
        p.setSavePath(savePath);
        //成功得到保存路径，所以注释掉了
//        qDebug() << "pictureUtils对象成功得到保存路径: " << p.getSavePath();
    }
    int frameFinished=0;
    int pictureCount = 0;
    while (playing)
    {
        //暂停的时候就停在这个循环里
        while(neededPause)
        {
            currentState = PausedState;
            QThread::msleep(10);
        }
        int time0 = QTime::currentTime().msecsSinceStartOfDay();
        //跳跃时间的时候便进入这个判断语句，重新设置pAVFormatContext
        if (neededSeek){
            seekTime -= 4000000;
            seekTime = (seekTime > 0)?seekTime:0;
            int target= av_rescale_q(seekTime,av_get_time_base_q(),pAVFormatContext->streams[videoStreamIndex]->time_base);
            av_seek_frame(pAVFormatContext,videoStreamIndex,target+startPts,AVSEEK_FLAG_FRAME); //AV_TIME_BASE
            neededSeek = false;
            qDebug() << seekTime << "  seekTimeseekTimeseekTimeseekTimeseekTime";


            while(true){
                av_read_frame(pAVFormatContext, &pAVPacket);
                if(pAVPacket.stream_index==videoStreamIndex){
                    avcodec_decode_video2(pAVCodecContext, pAVFrame, &frameFinished, &pAVPacket);
                    if (frameFinished){
                        if(pAVFrame->key_frame){
                            av_free_packet(&pAVPacket);
                            break;
                        }
                    }
                    av_free_packet(&pAVPacket);
                }

            }
        }

        if (av_read_frame(pAVFormatContext, &pAVPacket) >= 0){

            if(startPts == -1){
                startPts = pAVPacket.pts;
            }

            if(pAVPacket.stream_index==videoStreamIndex){
                qDebug()<<"开始解码"<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                       << totalTime;
                avcodec_decode_video2(pAVCodecContext, pAVFrame, &frameFinished, &pAVPacket);
                if (frameFinished){
                    //通过当前的pts进行映射得到currentTime
                    currentTime = av_rescale_q(pAVFrame->pkt_pts-startPts, pAVFormatContext->streams[videoStreamIndex]->time_base,av_get_time_base_q());

//                    qDebug()<<"**********" <<  pAVFrame->pkt_pos << "***********" << pAVFrame->pkt_size<< "***********"
//                    << pAVFrame->pkt_duration<< "***********" << pAVFrame->pkt_dts
//                    <<"**********" <<currentTime <<"**********" <<  pAVFrame->pkt_pts;
//                    mutex.lock();
                    sws_scale(pSwsContext,(const uint8_t* const *)pAVFrame->data,pAVFrame->linesize,0,videoHeight,pAVPicture.data,pAVPicture.linesize);
                    //发送获取一帧图像信号
                    QImage image(pAVPicture.data[0],videoWidth,videoHeight,QImage::Format_RGB888);
//                    p.savePicture(image,pictureCount,videoWidth,videoHeight);
                    image = Helper::paintRedLine(image);
                    emit GetImage(image);
                    emit updateTime(currentTime);
                    currentState = PlayingState;
//                    mutex.unlock();
                }
            }
        }
        int time1 = QTime::currentTime().msecsSinceStartOfDay();
        int diff = 40 - (time1 - time0);
        if (diff > 0)
        {
            QThread::msleep(diff);
//            qDebug()<< "处理速度比较快，睡了这么多毫秒："<<diff;
        }
        else
        {
//            qDebug()<< "MP4报警啊 慢的一匹啊！"<< time1 - time0;
        }
        av_free_packet(&pAVPacket);//释放资源,否则内存会一直上升.
        pictureCount ++;
     }

}

void QFFmpeg::getSavePath(const QString s)
{
    savePath = s;
}
