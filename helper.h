#ifndef HELPER_H
#define HELPER_H

#endif // HELPER_H
#include <QtCore>
#include <QtGui>
#include <QtNetwork>
//missing qt_version > 5
#include <QtWidgets>
#include <QMessageBox>
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

       /*
        * 判断输入截取视频段开始时间，结束时间是否有误
        * 1 不符合0-0-0格式
        * 2 超出范围 必须大于0小于等于60
        * 3 结束时间大于开始时间
        * 4 结束时间或开始时间大于视频总时间
        * */
       static bool isInputTimeFormatRight(QString strTime, QString endTime,qint64 totalTime){
           QStringList strTimeList = strTime.split("-");
           if(strTimeList.size() != 3){
               return false;
           }
           int minutes = strTimeList.at(0).toInt();
           int seconds = strTimeList.at(1).toInt();
           int milliseconds = strTimeList.at(2).toInt();
           if(minutes<0||minutes>=60 ||seconds<0||seconds>=60||milliseconds<0||milliseconds>=1000){
               return false;
           }

           qint64 SXKstartTime = minutes*60*1000000+seconds*1000000+milliseconds*1000;
           QStringList endTimeList = endTime.split("-");
           if(endTimeList.size() != 3){
                 return false;
           }
           minutes = endTimeList.at(0).toInt();
           seconds = endTimeList.at(1).toInt();
           milliseconds = endTimeList.at(2).toInt();
           if(minutes<0||minutes>=60 ||seconds<0||seconds>=60||milliseconds<0||milliseconds>=1000){
                return false;
           }
           qint64 SXKendTime = minutes*60*1000000+seconds*1000000+milliseconds*1000;
           if(SXKstartTime >= SXKendTime ){
               return false;
           }

           if(SXKstartTime > totalTime || SXKendTime> totalTime ){
               return false;
           }

           return true;
       }

       /*
        * 从输入的02-25-60 string转化成对应的qint64
        * */
       static qint64 getTimeFromLineEdit(QString time){
           QStringList timeList = time.split("-");
           if(timeList.size() != 3) {
               qDebug() << "at helper.h 181 errorerrorerrorerrorerrorerrorerrorerrorerrorerrorerror";
               return -1;
           }
           int minutes = timeList.at(0).toInt();
           int seconds = timeList.at(1).toInt();
           int milliseconds = timeList.at(2).toInt();
           if(minutes<0||minutes>=60 ||seconds<0||seconds>=60||milliseconds<0||milliseconds>=1000){
               return -1;
           }
           qint64 SXKTime = minutes*60*1000000+seconds*1000000+milliseconds*1000;

           return SXKTime;
       }

       static QString getSavePictureName(QString path){
           QStringList l = path.split("\\");
           int lenth = l.length();
           QString picName = l.at(lenth-3) + "-" + l.at(lenth-2) + "-" + l.at(lenth-1);
           picName = path + "\\" + picName;
           return picName;
       }


};
