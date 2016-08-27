#ifndef HELPER_H
#define HELPER_H

#endif // HELPER_H
#include <QtCore>
#include <QtGui>
#include <QtNetwork>
//missing qt_version > 5
#include <QtWidgets>
#include <QImage>
#include <QtSql>
#include <QDebug>
#include <QFile>
#include <qmessagebox.h>

/* 说明：全局辅助操作类实现文件
 * 功能：判断文件是否存在、创建指定目录
 * 作者：罗海彪
 * 时间：2016-7-22
*/

class Helper : public QObject
{
public:

    //设置编码为UTF8
       static void setUTF8Code() {
   #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
           QTextCodec *codec = QTextCodec::codecForName("UTF-8");
           QTextCodec::setCodecForLocale(codec);
           QTextCodec::setCodecForCStrings(codec);
           QTextCodec::setCodecForTr(codec);
   #endif
       }

       //设置指定样式
       static void setStyle(const QString &qssFile) {
           QFile file(qssFile);
           if (file.open(QFile::ReadOnly)) {
               QString qss = QLatin1String(file.readAll());
               qApp->setStyleSheet(qss);
               QString PaletteColor = qss.mid(20, 7);
               qApp->setPalette(QPalette(QColor(PaletteColor)));
               file.close();
           }
       }

       //判断是否是IP地址
       static bool isIP(QString IP) {
           QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
           return RegExp.exactMatch(IP);
       }

       //文件夹是否存在
       static bool folderIsExist(QString strFolder) {
           QDir tempFolder(strFolder);
           return tempFolder.exists();
       }

       //文件是否存在
       static bool fileIsExist(QString strFile) {
           QFile tempFile(strFile);
           return tempFile.exists();
       }

       //遍历当前目录下所有文件夹并获得文件目录
       static void getfilePath(const QString &path, QList<QString> &pathList){
           QDir dir(path);
           QStringList list;
           QStringList::Iterator iter;
           list = dir.entryList(QDir::Dirs, QDir::Name);

           for(iter=list.begin(); iter!=list.end(); ++iter){
               if( "." == *iter ||".." == *iter )continue;
                   getfilePath( path+"\\"+*iter , pathList);
           }

           list = dir.entryList(QDir::Files, QDir::Name);
           QString subPath;
           QString wantedPath;
           QStringList filePostfix;
           for(iter=list.begin(); iter!=list.end(); ++iter){
               subPath = path + "\\" + *iter;
              wantedPath = *iter;
               filePostfix = wantedPath.split(".");
               if(filePostfix.at(1) == "mp4"|| filePostfix.at(1) =="avi"
                       ||filePostfix.at(1) == "flv" ||filePostfix.at(1) == "rmvb" ){
                  pathList.push_back(subPath);
               }
           }

       }

       /*
        * 在图片High与Width-High处设置像素为1的竖线
        * 返回设置好的图片
        * */
       static QImage paintRedLine(QImage image){
           int pos_w = image.width();
           int pos_h = image.height();
           for(int y = 0; y < image.height() ;++y ){
               image.setPixelColor(QPoint(pos_h-1 , y) , QColor(255 ,0,0));
               image.setPixelColor(QPoint(pos_w - pos_h, y) , QColor(255 ,0,0));
            }
           return image;
       }

       /*
        * 通过路径得到视频名
        * 参数为完整的路径
        * 返回视频名字
        * */
       static QString getVideoNameFromDir(QString dir){
           QStringList list = dir.split('\\');
           QString videoNameWithPostFix = list.at(list.length()-1);

           list = videoNameWithPostFix.split('.');
           return list.at(0);
       }

       /*
        * 用轮训设置暂停时间，单位毫秒
        * */
       static void pauseMs(int pauseTime){
           int time0 = QTime::currentTime().msecsSinceStartOfDay();
           int time1 = QTime::currentTime().msecsSinceStartOfDay();
           while((time1 - time0)<pauseTime)
           {
               time1 = QTime::currentTime().msecsSinceStartOfDay();
           }
       }

};
