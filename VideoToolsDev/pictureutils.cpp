#include "pictureutils.h"
#include <QDir>
#include <QImage>
#include <QDebug>

PictureUtils::PictureUtils(QObject *parent) : QObject(parent)
{

}

void PictureUtils::savePicture(QImage image,int pictureCount,int videoWidth,int videoHeight)
{
    QImage temp = image.copy(0,0,videoHeight,videoHeight);

    QString pictureLeftPath =  savePath + "-L";
    QString pictureRightPath = savePath + "-R";
    QDir dir;
    dir.mkpath(pictureLeftPath);
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
    temp.save(pictureRightPath);
}

void PictureUtils::setSavePath(const QString s)
{
    savePath = s;
}

QString PictureUtils::getSavePath()
{
    return savePath;
}
