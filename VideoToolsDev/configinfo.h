#ifndef CONFIGINFO_H
#define CONFIGINFO_H
#include <QString>


class ConfigInfo
{
public:
    ConfigInfo();

    static QString AppPath;   //the path of application
    static QString ServerIP;   //the ip of the server
    static int DeskWidth;     //usable desktop width
    static int DeskHeight;    //usable desktop heigh

    static QString AppTitle;  //window title
    static QString AppStyle;  //window style
    static bool AutoRun;      //auto run when computer start
    static QString LastConfig;//the software last config infomation

    static void ReadConfig();
    static void WriteConfig();
};

#endif // CONFIGINFO_H
