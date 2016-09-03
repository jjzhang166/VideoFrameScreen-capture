#include "pictureutils.h"
#include "helper.h"
#include <QDir>
#include <QImage>
#include <QDebug>
#include <QMessageBox>

PictureUtils::PictureUtils(QObject *parent) : QObject(parent)
{

}

void PictureUtils::savePicture(QImage image,int radioType ,int pictureCount,int videoWidth,int videoHeight)
{
    QImage temp = image.copy(0,0,videoHeight,videoHeight);
    //对savePath加多判断，如果最后结尾是0~3的话，将savepath最后数字取出

    QString savePath_cp = savePath;  //保存个副本，防止savePath被改变
    QStringList savePathList  = savePath_cp.split("\\") ;
    int lenthSavePath = savePathList.length();
    int numSeted = savePathList.at(lenthSavePath-1).toInt();
    QString videoName = savePathList.at(lenthSavePath-2);

    QString LeftPathRadioS;
    QString RightPathRadioS;
    if(numSeted >= 0 || numSeted <4){
        QString str = savePathList.at(0);
        for(int k =1 ; k < lenthSavePath-2 ;++k){ //去掉视频名和最后的数字
            str = str +"\\"+ savePathList.at(k);
        }
        savePath_cp = str+"\\";
        //qDebug()<<"savePath is:"<<savePath;
        LeftPathRadioS = savePath_cp+ "L";
        RightPathRadioS = savePath_cp+ "R";
    }

    QString pictureLeftPath =  savePath + "-L";
    QString pictureRightPath = savePath + "-R";
    QDir dir;
/*  dir.mkpath(pictureLeftPath);
    dir.mkpath(pictureRightPath);
    QString tempS = QString::number(pictureCount);
    pictureLeftPath += "\\" + tempS + ".jpg";
    pictureRightPath += "\\" + tempS+ ".jpg";
//    qDebug() << "pictureLeftPath" << pictureLeftPath;
//    qDebug() << "pictureRightPath" << pictureRightPath;
    if(temp.save(pictureLeftPath)){
//        qDebug() << "save success";
    }
    else{
        qDebug() << "save failed";
    }
    temp = image.copy(videoWidth-videoHeight,0,videoHeight,videoHeight);
    temp.save(pictureRightPath);               */

    QString tempS = QString::number(pictureCount);
    if(radioType == 1){
        dir.mkpath(pictureLeftPath);
        dir.mkpath(pictureRightPath);
        pictureLeftPath = Helper::getSavePictureName(pictureLeftPath) + "-" + tempS + ".jpg";
        pictureRightPath = Helper::getSavePictureName(pictureRightPath) +"-" + tempS + ".jpg";

        if(!temp.save(pictureLeftPath)){
             qDebug()<<"save failed";
        }
        QImage temp2 = image.copy(videoWidth-videoHeight,0,videoHeight,videoHeight);
        if(!temp2.save(pictureRightPath)){
             qDebug()<<"save failed";
        }
    }else if(radioType == 2){
        dir.mkpath(pictureLeftPath);
        pictureLeftPath = Helper::getSavePictureName(pictureLeftPath) + "-" + tempS + ".jpg";
        if(!temp.save(pictureLeftPath)){
             qDebug()<<"save failed";
        }
    }else if(radioType == 3){
        dir.mkpath(pictureRightPath);
        pictureRightPath = Helper::getSavePictureName(pictureRightPath) +"-" + tempS + ".jpg";
        QImage temp2 = image.copy(videoWidth-videoHeight,0,videoHeight,videoHeight);
        if(!temp2.save(pictureRightPath)){
             qDebug()<<"save failed";
        }
    }else if(radioType == 4){
        dir.mkpath(LeftPathRadioS);
        dir.mkpath(RightPathRadioS);
        LeftPathRadioS = Helper::getSavePictureName(LeftPathRadioS  , numSeted) +"-" + videoName+ "-" + tempS + ".jpg" ;
        RightPathRadioS = Helper::getSavePictureName(RightPathRadioS, numSeted) +"-" + videoName+ "-" + tempS + ".jpg" ;
        qDebug()<<"LeftPathRadioS:"<<LeftPathRadioS;
        if(!temp.save(LeftPathRadioS)){
             qDebug()<<"save failed";
        }
        QImage temp2 = image.copy(videoWidth-videoHeight,0,videoHeight,videoHeight);
        if(!temp2.save(RightPathRadioS)){
             qDebug()<<"save failed";
        }
    }else{
        qDebug()<<"radioButton choose error!!";
    }











}

void PictureUtils::setSavePath(const QString s)
{
    savePath = s;
}

QString PictureUtils::getSavePath()
{
    return savePath;
}
