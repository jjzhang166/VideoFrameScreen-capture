#ifndef HELPER_H
#define HELPER_H

#endif // HELPER_H
#include <QtCore>
#include <QtGui>
#include <QtNetwork>
//missing qt_version > 5
#include <QtWidgets>
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
           for(iter=list.begin(); iter!=list.end(); ++iter){
               subPath = path + "\\" + *iter;
               pathList.push_back(subPath);
           }

       }

};
