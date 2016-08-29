#ifndef PICTUREUTILS_H
#define PICTUREUTILS_H

#include <QImage>

/*
 * 保存图片到指定路径
 * 截取图片左边，右边等
 * */
class PictureUtils : public QObject
{
    Q_OBJECT
public:
    explicit PictureUtils(QObject *parent = 0);
    void savePicture(QImage q,int radioType , int pictureCount,int videoWidth,int videoHeight);
    QString getSavePath();
    void setSavePath(const QString s);

signals:


private:
    QString savePath;
};

#endif // PICTUREUTILS_H
