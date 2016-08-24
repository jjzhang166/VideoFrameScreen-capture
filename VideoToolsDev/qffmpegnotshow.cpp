#include "qffmpegnotshow.h"
#include "pictureutils.h"
#include <QDebug>
#include <QTime>
#include <QThread>

QFFmpegNotShow::QFFmpegNotShow() : QFFmpeg()
{

}

void QFFmpegNotShow::playLocal()
{
    totalTime = pAVFormatContext->duration;
    totalTime = totalTime*96/100;//我也不知道为什么总时间就只有这么长



    PictureUtils p;
    if (savePath.isEmpty())
    {
        qDebug() << "传过来的保存路径是空";
    }
    else
    {
        //得到保存路径
        p.setSavePath(savePath);
    }
    int frameFinished=0;
    int pictureCount = 0;
    while (playing)
    {
        int time0 = QTime::currentTime().msecsSinceStartOfDay();

        if (av_read_frame(pAVFormatContext, &pAVPacket) >= 0){
            //对某些视频给初始的pts赋值,直接通过seek找到开始解码的位置
            if(startPts == -1){
                startPts = pAVPacket.pts;
                int target= av_rescale_q(startTime,av_get_time_base_q(),pAVFormatContext->streams[videoStreamIndex]->time_base);
                av_seek_frame(pAVFormatContext,videoStreamIndex,target+startPts,AVSEEK_FLAG_FRAME); //AV_TIME_BASE
                av_read_frame(pAVFormatContext, &pAVPacket);
            }

            if(pAVPacket.stream_index==videoStreamIndex){//如果当前的package是视频流
                qDebug()<<"开始解码"<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                       << " 总时长us："<< totalTime;
                avcodec_decode_video2(pAVCodecContext, pAVFrame, &frameFinished, &pAVPacket);
                if (frameFinished){
                    //通过当前的pts进行映射得到currentTime
                    currentTime = av_rescale_q(pAVFrame->pkt_pts-startPts, pAVFormatContext->streams[videoStreamIndex]->time_base,av_get_time_base_q());
                    sws_scale(pSwsContext,(const uint8_t* const *)pAVFrame->data,pAVFrame->linesize,0,videoHeight,pAVPicture.data,pAVPicture.linesize);
                    //发送获取一帧图像信号
                    QImage image(pAVPicture.data[0],videoWidth,videoHeight,QImage::Format_RGB888);
                    p.savePicture(image,pictureCount,videoWidth,videoHeight);
                }
            }
        }
        int time1 = QTime::currentTime().msecsSinceStartOfDay();
        qDebug()<< "保存图片花费了这么多毫秒："<<time1-time0
                << "  当前时间是us： "<< currentTime
                << "  保存图片张数： "<<pictureCount;

        av_free_packet(&pAVPacket);//释放资源,否则内存会一直上升.
        pictureCount ++;
        if(currentTime>endTime)
        {//播放结束
            break;
        }
     }

}
