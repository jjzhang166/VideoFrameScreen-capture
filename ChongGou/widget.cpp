#include "widget.h"
#include "ui_widget.h"
#include "playthread.h"
#include "qffmpegnotshow.h"
#include "qthreadnotshow.h"
#include "helper.h"

#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QListWidgetItem>
#include <QCursor>
#include <QKeyEvent>
#include <QThread>
#include <QTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    f = new QFFmpeg(this);
    thread = new PlayThread(this);
    thread->setffmpeg(f);

    ui->horizontalSlider->setRange(0,1000);

    connect(ui->pushButtonOpen,SIGNAL(clicked(bool)),this,SLOT(showVideoName()));
    connect(ui->pushButtonSavePath,SIGNAL(clicked(bool)),this,SLOT(getSavePathRoot()));
    connect(ui->pushButtonSavePicture,SIGNAL(clicked(bool)),this,SLOT(saveVideoPicture()));
    connect(ui->pushButtonDingWeiStart,SIGNAL(clicked(bool)),this,SLOT(seekAndStopStart()));
    connect(ui->pushButtonDingWeiEnd,SIGNAL(clicked(bool)),this,SLOT(seekAndStopEnd()));


    connect(ui->listWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(playAndSaveVideo()));
    connect(ui->pushButtonPlay,SIGNAL(clicked(bool)),this,SLOT(playPause()));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(slotValueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setImage( const QImage &image)
{
    ui->labelVideo->setPixmap(QPixmap::fromImage(image));
}

void Widget::slotPlayVideo()
{
    if (ui->lineEdit->text() == 0)
    {
        QMessageBox::warning(this,"Warning","Please input address",QMessageBox::Ok);
    }
    else
    {
        resetQFFmpeg();
        QFFmpeg *temp = f; //用来保存ffmpeg原来指向的空间并在代码块最后释放
        QFFmpeg *temp2 = new QFFmpeg(this);

        QString currentDir = ui->listWidget->currentItem()->text();

        temp2->SetUrl(currentDir);
        ui->lineEdit->setText(currentDir);
        qDebug() << ui->lineEdit->text();
        if(temp2->Init()){
            f = temp2;

            connect(f,SIGNAL(GetImage(QImage)),this,SLOT(setImage(QImage)));
            connect(this,SIGNAL(sendSavePath(QString)),f,SLOT(getSavePath(QString)));
            connect(f,SIGNAL(updateTime(qint64)),this,SLOT(slotUpdateTime(qint64)));
            emit sendSavePath(saveSXKPath);

            thread->setffmpeg(f);
            thread->setFlag(true);

            thread->start();
        }
        else
        {
            f = temp2;//此时失败后ffmpeg便没有运行play方法
            QMessageBox::warning(this,"Warning","ffmpeg init failed",QMessageBox::Ok);
            ui->labelVideo->clear();
        }
        delete temp;
        temp = Q_NULLPTR;
    }

}

/*
 * 点击打开文件后发生的事件
 * 通过输入的路径将文件夹下面的所有video视频在listWidget中显示出来
 *
 * */
void Widget::showVideoName()
{

    if(ui->lineEditOpen->text().isEmpty())
    {
        QMessageBox::warning(this,"","输入不能为空",QMessageBox::Ok);
    }
    else
    {
        QString openPath = ui->lineEditOpen->text();
        ui->lineEdit->setText(openPath);
        qDebug() << openPath;

        QDir dir(openPath);
        if(dir.exists()){
            ui->listWidget->clear();
            QList<QString> pathList;
            Helper::getfilePath(openPath ,pathList );
            if(pathList.size() == 0){
                QMessageBox::warning(this,"","文件不存在",QMessageBox::Ok);
            }else{
                for(int i =0; i < pathList.size() ; ++i)
                     ui->listWidget->addItem(pathList[i]);
            }

        }else{
           QMessageBox::warning(this,"","文件夹不存在",QMessageBox::Ok);
        }
    }

}

/*
 * 双击列表里的视频后会发生的事件
 * */
void Widget::playAndSaveVideo()
{
    ui->lineEdit->clear();
    if(ui->lineEditSave->text().isEmpty())
    {
        QMessageBox::about(this,"","保存路径不能为空！");
    }
    else
    {
        qDebug() << "成功双击了列表里的视频";
        QListWidgetItem *selectedItem = ui->listWidget->itemAt(
                    ui->listWidget->mapFromGlobal(QCursor::pos()));

        if ( selectedItem )
        {
            //得到视频名称,取消后缀，加入根目录路径中
            ui->lineEdit->setText(ui->listWidget->currentItem()->text());
            QString videoName = Helper::getVideoNameFromDir(ui->listWidget->currentItem()->text());//取消后缀
            saveSXKPath    = savePathRoot + "上下客样本"+"\\" + videoName + "\\" + videoName;
            saveFSXKLPath  = savePathRoot + "非上下客样本左"+"\\" + videoName + "\\" + videoName;
            saveFSXKRPath  = savePathRoot + "非上下客样本右"+"\\" + videoName + "\\" + videoName;
            saveGDSXKLPath = savePathRoot + "过度上下客样本左" +"\\" + videoName + "\\" + videoName;
            saveGDSXKRPath = savePathRoot + "过度上下客样本右" +"\\" + videoName + "\\" + videoName;
            this->slotPlayVideo();
        }
    }
}

void Widget::getSavePathRoot()
{
    if(ui->lineEditSave->text().isEmpty())
    {
        QMessageBox::warning(this,"","输入不能为空",QMessageBox::Ok);
    }
    else
    {
        savePathRoot = ui->lineEditSave->text();
        savePathRoot += "\\";
        QString show = "设置保存路径成功，保存路径为：";
        QMessageBox::warning(this,"",show,QMessageBox::Ok);
    }
}

void Widget::resetQFFmpeg()
{
    thread->getFFmpeg()->setPause(false);
    thread->getFFmpeg()->setPlaying(false);
    thread->setFlag(false);
    int count = 0;
    while(thread->isRunning())
    {
        qDebug() << "又要等子线程停下来才能设置过新的线程" << count++;
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace )
    qDebug() << "***************************************************************************";
}

/*
 * 点击暂停按钮发生的事件
 * */

void Widget::playPause()
{
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState)
    {
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }
    else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState)
    {
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    else if (thread->getFFmpeg()->getState() == QFFmpeg::StoppedState)
    {
        qDebug() <<"now the state is StoppedState";
    }
}

void Widget::slotUpdateTime(qint64 time)
{
    double v = time*10000.0/(thread->getFFmpeg()->getTotalTime()*10.0);
//    qDebug() << "给slider设置的value：" << v;
    ui->horizontalSlider->setValue(v);
    //ui->lineEditProcess->setText(QString("%1").arg(v));
    long minVal = time/(60*(1e+6));
    long secVal = (time - minVal* 60*(1e+6))/(1e+6);
    long millisecVal = (time - minVal* 60*(1e+6) -secVal*(1e+6) )/1000;
    QString minStr = QString::number(minVal , 10);
    QString secStr = QString::number(secVal , 10);
    QString millisecStr = QString::number(millisecVal , 10);
    QString timeStr = minStr + "-"+ secStr +"-"+ millisecStr;
    ui->lineEditProcess->setText(timeStr);
}

void Widget::slotValueChanged(int value)
{
    qint64 v = (value/1000.0)*thread->getFFmpeg()->getTotalTime();
    thread->getFFmpeg()->setSeekAndSeekTime(true,v);//传入设置的value值
}

/*
 * 点击add按钮发生的事情
 * */

void Widget::saveVideoPicture()
{
        //得到截取视频的起始时间和终止时间的long值
    //将输入的时间格式转换为微秒，by zjy
    QString strTime =  ui->lineEditBegin->text();
    QStringList strTimeList = strTime.split("-");
    if(strTimeList.size() != 3){
         QMessageBox::warning(this,"","上下客截取时间格式有误！",QMessageBox::Ok);
         return;
    }
    int minutes = strTimeList.at(0).toInt();
    int seconds = strTimeList.at(1).toInt();
    int milliseconds = strTimeList.at(2).toInt();
    if(minutes<0||minutes>=60 ||seconds<0||seconds>=60||milliseconds<0||milliseconds>=1000){
        QMessageBox::warning(this,"","上下客截取时间格式有误！",QMessageBox::Ok);
        return;
    }
    qint64 SXKstartTime = minutes*60*1000000+seconds*1000000+milliseconds*1000;
    strTime = ui->lineEditEnd->text();
    strTimeList = strTime.split("-");
    if(strTimeList.size() != 3){
         QMessageBox::warning(this,"","上下客截取时间格式有误！",QMessageBox::Ok);
         return;
    }
    minutes = strTimeList.at(0).toInt();
    seconds = strTimeList.at(1).toInt();
    milliseconds = strTimeList.at(2).toInt();
    if(minutes<0||minutes>=60 ||seconds<0||seconds>=60||milliseconds<0||milliseconds>=1000){
        QMessageBox::warning(this,"","上下客截取时间格式有误！",QMessageBox::Ok);
        return;
    }
    qint64 SXKendTime = minutes*60*1000000+seconds*1000000+milliseconds*1000;
    if(SXKstartTime >= SXKendTime ){
        QMessageBox::warning(this,"","开始时间不能大于结束时间！",QMessageBox::Ok);
        return;
    }
    if(SXKstartTime >thread->getFFmpeg()->getTotalTime() || SXKendTime> thread->getFFmpeg()->getTotalTime()){
        QMessageBox::warning(this,"","开始时间或结束时间超出范围！",QMessageBox::Ok);
        return;
    }

    qint64 totalTime = thread->getFFmpeg()->getTotalTime()*96/100;
    if(ui->lineEditBegin->text().isEmpty() || ui->lineEditEnd->text().isEmpty() )
    {
        QMessageBox::warning(this,"","开始位置或结束位置不能为空",QMessageBox::Ok);
    }
    else
    {
        //截取上下客视频
        savePicture(SXKstartTime,SXKendTime,0);


        //得到过度上下客左侧的起始时间和终止时间的long值
        qint64 GDLstartTime = SXKstartTime - 20000000;
        qint64 GDLendTime = SXKstartTime;
        if ( GDLstartTime > 0 )
        {
//            qDebug() << "***************GDLstartTime" << GDLstartTime;
            savePicture_LR(GDLstartTime,GDLendTime,1);

             //得到非上下客左侧的起始时间和终止时间的long值
            qint64 FLstartTime = 0;
            qint64 FLendTime = GDLstartTime;
            savePicture_LR(FLstartTime,FLendTime,3);
        }
        else // 如果过度上下客的开始时间小于0，就从0开始截取
        {
            savePicture_LR(0,GDLendTime,1);
        }

        //得到过度上下客右侧的起始时间和终止时间的long值
        qint64 GDRstartTime = SXKendTime;
        qint64 GDRendTime = SXKendTime + 20000000;
        if ( GDRendTime < totalTime )
        {
//            qDebug() << "***************GDRendTime" << GDRendTime;
            savePicture_LR(GDRstartTime,GDRendTime,2);

            //得到非上下客右侧的起始时间和终止时间的long值
            qint64 FRstartTime = GDRendTime;
            qint64 FRendTime = totalTime;
            savePicture_LR(FRstartTime,FRendTime,4);
        }
        else// 如果过度上下客右侧的终止时间大于总时间，那么总时间就是终止时间
        {
            savePicture_LR(GDRstartTime,totalTime,2);
        }

        setVideoAlreadySave();//设置已保存
    }
    ui->lineEditBegin->clear();
    ui->lineEditEnd->clear();
}

/*
 *  保存上下客图片 type=0是上下客 1是过度上下客left 2是过度上下客right 3 非上下客left 4非上下客right
 **/
void Widget::savePicture(qint64 startTime,qint64 endTime,int type)
{
    QFFmpegNotShow *ffmpegNotShow = new QFFmpegNotShow();
    //设置给相应的ffmpeg
    ffmpegNotShow->setStartTime(startTime);
    ffmpegNotShow->setEndTime(endTime);

    qDebug() << startTime << "*****************" << endTime;

    QThreadNotShow *t = new QThreadNotShow();
    t->setFFmpeg(ffmpegNotShow);

    //读取radioButton的选中状态
    if(ui->radioLR->isChecked()){
         ffmpegNotShow->setSaveType(1);
    }else if(ui->radioLeft->isChecked()){
         ffmpegNotShow->setSaveType(2);
    }else{
         ffmpegNotShow->setSaveType(3);
    }


    ffmpegNotShow->SetUrl(ui->lineEdit->text());
    if(ffmpegNotShow->Init()){

        connect(this,SIGNAL(sendSavePath(QString)),ffmpegNotShow,SLOT(getSavePath(QString)));
        if (type == 0)
        {
            emit sendSavePath(saveSXKPath);
            qDebug() << "保存上下客视频" << saveSXKPath;
        }
        else if (type == 1 )
        {
            emit sendSavePath(saveGDSXKLPath);
            qDebug() << "保存上下客视频" << saveGDSXKLPath;
        }
        else if (type == 2 )
        {
            emit sendSavePath(saveGDSXKRPath);
            qDebug() << "保存上下客视频" << saveGDSXKRPath;
        }
        else if (type == 3 )
        {
            emit sendSavePath(saveFSXKLPath);
            qDebug() << "保存上下客视频" << saveFSXKLPath;
        }
        else if (type == 4 )
        {
            emit sendSavePath(saveFSXKRPath);
            qDebug() << "保存上下客视频" << saveFSXKRPath;
        }

        t->start();
    }
    else
    {
        QMessageBox::warning(this,"Warning","ffmpeg init failed",QMessageBox::Ok);
        ui->labelVideo->clear();
    }
}

void Widget::savePicture_LR(qint64 startTime, qint64 endTime, int type)
{
    QFFmpegNotShow *ffmpegNotShow = new QFFmpegNotShow();
    //设置给相应的ffmpeg
    ffmpegNotShow->setStartTime(startTime);
    ffmpegNotShow->setEndTime(endTime);

    qDebug() << startTime << "*****************" << endTime;

    QThreadNotShow *t = new QThreadNotShow();
    t->setFFmpeg(ffmpegNotShow);

    ffmpegNotShow->setSaveType(1); //默认全截左右两边

    ffmpegNotShow->SetUrl(ui->lineEdit->text());
    if(ffmpegNotShow->Init()){

        connect(this,SIGNAL(sendSavePath(QString)),ffmpegNotShow,SLOT(getSavePath(QString)));
        if (type == 0)
        {
            emit sendSavePath(saveSXKPath);
            qDebug() << "保存上下客视频" << saveSXKPath;
        }
        else if (type == 1 )
        {
            emit sendSavePath(saveGDSXKLPath);
            qDebug() << "保存上下客视频" << saveGDSXKLPath;
        }
        else if (type == 2 )
        {
            emit sendSavePath(saveGDSXKRPath);
            qDebug() << "保存上下客视频" << saveGDSXKRPath;
        }
        else if (type == 3 )
        {
            emit sendSavePath(saveFSXKLPath);
            qDebug() << "保存上下客视频" << saveFSXKLPath;
        }
        else if (type == 4 )
        {
            emit sendSavePath(saveFSXKRPath);
            qDebug() << "保存上下客视频" << saveFSXKRPath;
        }

        t->start();
    }
    else
    {
        QMessageBox::warning(this,"Warning","ffmpeg init failed",QMessageBox::Ok);
        ui->labelVideo->clear();
    }
}

void Widget::setVideoAlreadySave()
{
    QString oldName = ui->listWidget->currentItem()->text();
    QString newName = "(alreadySave)"+oldName + "\n";

    QString fileName = savePathRoot + "视频信息.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qDebug() << file.errorString();
    }
    file.write(newName.toLatin1());
//    file.write("\n");
    file.close();
}

void Widget::seekAndStopStart()
{
    //转为时间微秒
    QString strTime =  ui->lineEditBegin->text();
    QStringList strTimeList = strTime.split("-");
    if(strTimeList.size() != 3){
         QMessageBox::warning(this,"","上下客定位开始时间格式有误！",QMessageBox::Ok);
         return;
    }
    int minutes = strTimeList.at(0).toInt();
    int seconds = strTimeList.at(1).toInt();
    int milliseconds = strTimeList.at(2).toInt();
    if(minutes<0||minutes>=60 ||seconds<0||seconds>=60||milliseconds<0||milliseconds>=1000){
        QMessageBox::warning(this,"","上下客定位开始时间格式有误！",QMessageBox::Ok);
        return;
    }
    qint64 v = minutes*60*1000000+seconds*1000000+milliseconds*1000;
    if(v > thread->getFFmpeg()->getTotalTime()){
        QMessageBox::warning(this,"","上下客定位开始时间超出范围！",QMessageBox::Ok);
        return;
    }

    //qint64 v = (ui->lineEditBegin->text().toDouble()/1000) * (thread->getFFmpeg()->getTotalTime());
    thread->getFFmpeg()->setSeekAndSeekTime(true,v);//传入设置的value值
    //不同线程通信，为了让FFmpeg的线程再找到frame后再停下来，这里先跑500ms
    Helper::pauseMs(500);
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState)
    {
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState)
    {
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    Helper::pauseMs(500);
    thread->getFFmpeg()->setPause(true);
}

void Widget::seekAndStopEnd()
{
    QString strTime =  ui->lineEditEnd->text();
    QStringList strTimeList = strTime.split("-");
    if(strTimeList.size() != 3){
         QMessageBox::warning(this,"","上下客定位开始时间格式有误！",QMessageBox::Ok);
         return;
    }
    int minutes = strTimeList.at(0).toInt();
    int seconds = strTimeList.at(1).toInt();
    int milliseconds = strTimeList.at(2).toInt();
    if(minutes<0||minutes>=60 ||seconds<0||seconds>=60||milliseconds<0||milliseconds>=1000){
        QMessageBox::warning(this,"","上下客定位开始时间格式有误！",QMessageBox::Ok);
        return;
    }
    qint64 v = minutes*60*1000000+seconds*1000000+milliseconds*1000;
    if(v > thread->getFFmpeg()->getTotalTime()){
        QMessageBox::warning(this,"","上下客定位开始时间超出范围！",QMessageBox::Ok);
        return;
    }

    //qint64 v = (ui->lineEditEnd->text().toDouble()/1000) * (thread->getFFmpeg()->getTotalTime());
    thread->getFFmpeg()->setSeekAndSeekTime(true,v);//传入设置的value值
    //不同线程通信，为了让FFmpeg的线程再找到frame后再停下来，这里先跑500ms
    Helper::pauseMs(500);
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState)
    {
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState)
    {
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    Helper::pauseMs(500);
    thread->getFFmpeg()->setPause(true);

}


