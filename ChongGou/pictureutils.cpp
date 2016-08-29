#include "pictureutils.h"
#include "helper.h"
#include <QDir>
#include <QImage>
#include <QDebug>

PictureUtils::PictureUtils(QObject *parent) : QObject(parent)
{

}

void PictureUtils::savePicture(QImage image,int radioType ,int pictureCount,int videoWidth,int videoHeight)
{
    QImage temp = image.copy(0,0,videoHeight,videoHeight);

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
