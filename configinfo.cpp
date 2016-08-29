#include "configinfo.h"
#include "helper.h"
#include <QDebug>

ConfigInfo::ConfigInfo()
{
    //ConfigInfo::AppPath = "";
}

QString ConfigInfo::AppPath = "";
int ConfigInfo::DeskWidth = 1024;
int ConfigInfo::DeskHeight = 768;

QString ConfigInfo::AppTitle = "交通违法行为识别系统";
QString ConfigInfo::ServerIP = "192.168.0.51";
QString ConfigInfo::AppStyle = "";
bool ConfigInfo::AutoRun = false;

QString ConfigInfo::LastConfig = "1";

void ConfigInfo::ReadConfig()
{
    QString fileName = ConfigInfo::AppPath + "config.txt";
    //qDebug() << fileName;

    /*
     * 如果文件不存在，设置个题目后，以上面的初始值运行
     * */
    if (!Helper::fileIsExist(fileName))
    {
        ConfigInfo::AppTitle = ConfigInfo::AppTitle.toLatin1(); //conver qstring into char* or bytearray
        //qDebug() << ConfigInfo::AppTitle;
        return;
    }

    QSettings *set = new QSettings(fileName,QSettings::IniFormat);
    set->beginGroup("AppConfig"); //begin the config text with this title
    ConfigInfo::AppTitle = set->value("AppTitle").toString();
    ConfigInfo::AppStyle = set->value("AppStyle").toString();
    ConfigInfo::ServerIP = set->value("ServerIP").toString();
    set->endGroup();

}

void ConfigInfo::WriteConfig()
{
    QString fileName = ConfigInfo::AppPath + "config.txt";
    QSettings *set = new QSettings(fileName,QSettings::IniFormat);

    set->beginGroup("AppConfig");
    set->setValue("AppTitle",ConfigInfo::AppTitle);
    qDebug() << ConfigInfo::AppTitle;
    qDebug()<<ConfigInfo::ServerIP;
    set->setValue("ServerIp",ConfigInfo::ServerIP);
    set->setValue("AppStyle",ConfigInfo::AppStyle);
    set->setValue("AutoRun",ConfigInfo::AutoRun);
//    set->setValue();
    qDebug() << "ConfigInfo::WriteConfig AutoRun" << ConfigInfo::AutoRun;
    set->setValue("LastConfig",ConfigInfo::LastConfig);
    set->endGroup();
}
