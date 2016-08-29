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
//                startPts = pAVFormatContext->streams[videoStreamIndex]->start_time;
                startTime -= 3000000;
                if(startTime < 0 ){
                    startTime = 0;
                }

                qDebug() << startTime << "  startTimestartTimestartTimestartTimestartTimestartTime";
                int target= av_rescale_q(startTime,av_get_time_base_q(),pAVFormatContext->streams[videoStreamIndex]->time_base);
                av_seek_frame(pAVFormatContext,videoStreamIndex,target+startPts,AVSEEK_FLAG_FRAME); //AV_TIME_BASE
                av_read_frame(pAVFormatContext, &pAVPacket);
                startTime += 3000000;
            }

            if(pAVPacket.stream_index==videoStreamIndex){//如果当前的package是视频流
                qDebug()<<"开始解码"<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                       << " 总时长us："<< totalTime;
                avcodec_decode_video2(pAVCodecContext, pAVFrame, &frameFinished, &pAVPacket);
                if (frameFinished){
                    //通过当前的pts进行映射得到currentTime
                    currentTime = av_rescale_q(pAVFrame->pkt_pts-startPts, pAVFormatContext->streams[videoStreamIndex]->time_base,av_get_time_base_q());
                    if (currentTime > startTime ){
                        sws_scale(pSwsContext,(const uint8_t* const *)pAVFrame->data,pAVFrame->linesize,0,videoHeight,pAVPicture.data,pAVPicture.linesize);
                        QImage image(pAVPicture.data[0],videoWidth,videoHeight,QImage::Format_RGB888);
                        p.savePicture(image, type ,pictureCount,videoWidth,videoHeight);  //加多type判断
                        pictureCount ++;
                    }
                }
            }
        }
        int time1 = QTime::currentTime().msecsSinceStartOfDay();
        qDebug()<< "保存图片花费了这么多毫秒："<<time1-time0
                << "  当前时间是us： "<< currentTime
                << "  保存图片张数： "<< pictureCount
                << "  开始时间是："<< startTime
                << "  结束时间是us：" << endTime;
        av_free_packet(&pAVPacket);//释放资源,否则内存会一直上升.
        qDebug() << "保存路径为： "<< p.getSavePath();
        if(currentTime>endTime || pictureCount > 10000)
        {//播放结束
            break;
        }
     }

}
