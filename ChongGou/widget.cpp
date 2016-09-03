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

    connect(ui->pushButtonOpen,SIGNAL(clicked(bool)),this,SLOT(slotShowVideoName()));
    connect(ui->pushButtonSavePicture,SIGNAL(clicked(bool)),this,SLOT(slotSaveVideoPicture()));
    connect(ui->pushButtonDingWeiStart,SIGNAL(clicked(bool)),this,SLOT(slotSeekAndStopStart()));
    connect(ui->pushButtonDingWeiEnd,SIGNAL(clicked(bool)),this,SLOT(slotSeekAndStopEnd()));


    connect(ui->listWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slotPlayAndSaveVideo()));
    connect(ui->pushButtonPlay,SIGNAL(clicked(bool)),this,SLOT(slotPlayPause()));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(slotValueChanged(int)));

    ui->horizontalSlider->installEventFilter(this);
    ui->pushButtonPlay->installEventFilter(this);
    ui->lineEditSetGapTime->installEventFilter(this);
    ui->listWidget->installEventFilter(this);
    ui->labelVideo->installEventFilter(this);
    installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotSetImage( const QImage &image)
{
    ui->labelVideo->setPixmap(QPixmap::fromImage(image));
}

void Widget::slotPlayVideo()
{
    if (ui->lineEdit->text() == 0){
        QMessageBox::warning(this,"Warning","Please input address",QMessageBox::Ok);
    }
    else{
        resetQFFmpeg();
        QFFmpeg *temp = f; //用来保存ffmpeg原来指向的空间并在代码块最后释放
        QFFmpeg *temp2 = new QFFmpeg(this);

        QString currentDir = ui->listWidget->currentItem()->text();

        temp2->SetUrl(currentDir);
        ui->lineEdit->setText(currentDir);
        qDebug() << ui->lineEdit->text();
        if(temp2->Init()){
            f = temp2;

            connect(f,SIGNAL(GetImage(QImage)),this,SLOT(slotSetImage(QImage)));
            connect(this,SIGNAL(sendSavePath(QString)),f,SLOT(getSavePath(QString)));
            connect(f,SIGNAL(updateTime(qint64)),this,SLOT(slotUpdateTime(qint64)));
            emit sendSavePath(saveSXKPath);

            thread->setffmpeg(f);
            thread->setFlag(true);

            thread->start();
        }
        else{
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
 * 1 输入为空 退出
 * 2 路径不存在 退出
 * 3 文件不存在 退出
 * */
void Widget::slotShowVideoName()
{

    if(ui->lineEditOpen->text().isEmpty()){
        QMessageBox::warning(this,"","输入不能为空",QMessageBox::Ok);
        return;
    }

    QString openPath = ui->lineEditOpen->text();
    ui->lineEdit->setText(openPath);
    qDebug() << openPath;

    QDir dir(openPath);
    if(!dir.exists()){
       QMessageBox::warning(this,"","文件夹不存在",QMessageBox::Ok);
       return;
    }

    ui->listWidget->clear();
    QList<QString> pathList;
    Helper::getfilePath(openPath ,pathList );
    if(pathList.size() == 0){
        QMessageBox::warning(this,"","文件不存在",QMessageBox::Ok);
        return;
    }
    for(int i =0; i < pathList.size() ; ++i)
         ui->listWidget->addItem(pathList[i]);
}

/*
 * 双击列表里的视频后会发生的事件
 * 1 保存路径不能为空 否则退出
 * 2 双击视频列表 若没有选中 退出
 * */
void Widget::slotPlayAndSaveVideo()
{
    ui->lineEdit->clear();

    qDebug() << "成功双击了列表里的视频";
    if(!slotGetSavePathRoot()){
        return;
    }

    QListWidgetItem *selectedItem = ui->listWidget->itemAt(
                ui->listWidget->mapFromGlobal(QCursor::pos()));
    if ( !selectedItem ){
        return;
    }
    //得到视频名称,取消后缀，加入根目录路径中
    ui->lineEdit->setText(ui->listWidget->currentItem()->text());
    QString videoName = Helper::getVideoNameFromDir(ui->listWidget->currentItem()->text());//取消后缀
    //暂时标记为1 箭头对
    saveSXKPath    = savePathRoot + "上下客样本"+"\\" + videoName + "\\" + "1";
    saveFSXKLPath  = savePathRoot + "非上下客样本左"+"\\" + videoName + "\\" + "1";
    saveFSXKRPath  = savePathRoot + "非上下客样本右"+"\\" + videoName + "\\" + "1";
    saveGDSXKLPath = savePathRoot + "过度上下客样本左" +"\\" + videoName + "\\" + "1";
    saveGDSXKRPath = savePathRoot + "过度上下客样本右" +"\\" + videoName + "\\" + "1";
    this->slotPlayVideo();

}

bool Widget::slotGetSavePathRoot()
{
    if(ui->lineEditSave->text().isEmpty()){
        QMessageBox::warning(this,"","保存路径不能为空",QMessageBox::Ok);
        return false;
    }
    else{
        savePathRoot = ui->lineEditSave->text();
        savePathRoot += "\\";
        return true;
    }
}

void Widget::resetQFFmpeg()
{
    thread->getFFmpeg()->setPause(false);
    thread->getFFmpeg()->setPlaying(false);
    thread->setFlag(false);
    int count = 0;
    while(thread->isRunning()){
        qDebug() << "又要等子线程停下来才能设置过新的线程" << count++;
    }
}

/*
 * 点击暂停按钮发生的事件
 * */

void Widget::slotPlayPause()
{
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState){
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }
    else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState){
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    else if (thread->getFFmpeg()->getState() == QFFmpeg::StoppedState){
        qDebug() <<"now the state is StoppedState";
    }
}

void Widget::slotUpdateTime(qint64 time)
{
    double v = time*10000.0/(thread->getFFmpeg()->getTotalTime()*10.0);
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
 * 1 如果没有视频播放则退出
 * */

void Widget::slotSaveVideoPicture()
{
    //得到截取视频的起始时间和终止时间的long值
    //将输入的时间格式转换为微秒，by zjy

    if(thread->getFFmpeg()->getState() != QFFmpeg::PlayingState){
        QMessageBox::about(this,"","只能保存当前正在播放的视频，当前无视频播放不保存图片");
        return;
    }

    savePathRoot = ui->lineEditSave->text();
    savePathRoot += "\\";  //更新savePathRoot
    QString videoName = Helper::getVideoNameFromDir(ui->listWidget->currentItem()->text());//取消后缀
    saveSXKSetedPath = savePathRoot + videoName;//s键按下的时候的路径

    qint64 totalTime = thread->getFFmpeg()->getTotalTime()*96/100;
    if(ui->lineEditBegin->text().isEmpty() && ui->lineEditEnd->text().isEmpty() ){//同时为空
        qint64 GDLstartTime = 1;
        savePicture(GDLstartTime ,totalTime,3 );
        return ;
    }

    if (!Helper::isInputTimeFormatRight(ui->lineEditBegin->text()
            ,ui->lineEditEnd->text(),totalTime) ){
        QMessageBox::warning(this,"","开始时间或结束时间输入有误！",QMessageBox::Ok);
        return;
    }

    if(ui->lineEditBegin->text().isEmpty() || ui->lineEditEnd->text().isEmpty() ){
        QMessageBox::warning(this,"","开始位置或结束位置不能为空",QMessageBox::Ok);
    }
    else{
        //截取上下客视频
        qint64 SXKstartTime = Helper::getTimeFromLineEdit(ui->lineEditBegin->text());
        qint64 SXKendTime = Helper::getTimeFromLineEdit(ui->lineEditEnd->text());
        if(ui->radioS->isChecked()){ //若s按钮按下的
             savePicture(SXKstartTime,SXKendTime,0);
             setVideoAlreadySave();//设置已保存
             return;
        }
        savePicture(SXKstartTime,SXKendTime,0);

        //得到过度上下客左侧的起始时间和终止时间的long值
        qint64 GDLstartTime = SXKstartTime - ui->lineEditSetGDTime->text().toDouble()*1000000;
        qint64 GDLendTime = SXKstartTime;
        if ( GDLstartTime > 0 ){
            savePicture(GDLstartTime,GDLendTime,1);

             //得到非上下客左侧的起始时间和终止时间的long值
            qint64 FLstartTime = 0;
            qint64 FLendTime = GDLstartTime;
            savePicture(FLstartTime,FLendTime,3);
        }
        else {// 如果过度上下客的开始时间小于0，就从1秒处开始截取
            savePicture(1000000,GDLendTime,1);
        }

        //得到过度上下客右侧的起始时间和终止时间的long值
        qint64 GDRstartTime = SXKendTime;
        qint64 GDRendTime = SXKendTime + ui->lineEditSetGDTime->text().toDouble()*1000000;
        if ( GDRendTime < totalTime ){
            savePicture(GDRstartTime,GDRendTime,2);

            //得到非上下客右侧的起始时间和终止时间的long值
            qint64 FRstartTime = GDRendTime;
            qint64 FRendTime = totalTime;
            savePicture(FRstartTime,FRendTime,4);
        }
        else{// 如果过度上下客右侧的终止时间大于总时间，那么总时间就是终止时间
            savePicture(GDRstartTime,totalTime,2);
        }
        setVideoAlreadySave();//设置已保存
    }
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

    qDebug() << "传给ffmpegNotShow的开始时间是：" << startTime
             << "传给ffmpegNotShow的结束时间是：" << endTime;

    QThreadNotShow *t = new QThreadNotShow();
    t->setFFmpeg(ffmpegNotShow);

    //读取radioButton的选中状态 只有上下客样本才要区分左右，其余默认左右
    if(type == 0){
        if(ui->radioLR->isChecked()){
             ffmpegNotShow->setSaveType(1);
        }else if(ui->radioLeft->isChecked()){
             ffmpegNotShow->setSaveType(2);
        }else if(ui->radioRight->isChecked()){
             ffmpegNotShow->setSaveType(3);
        }else{

            ffmpegNotShow->setSaveType(4);  //不是前三种，QFFmpegNotShow的type设置为4
            QString setNumber = ui->lineEditSetSavePath->text();
            int numberSet = setNumber.toInt();
            if( numberSet< 0 ||numberSet>3 ){
                QMessageBox::warning(this,"","输入范围必须是0~3！",QMessageBox::Ok);
                return;
            }
            saveSXKSetedPath = saveSXKSetedPath +"\\" + setNumber ; //加入视频号和所选设置号
            qDebug()<<"saveSXKSetedPath: "  <<  saveSXKSetedPath;
        }
    }
    else{
        ffmpegNotShow->setSaveType(1);
    }


    ffmpegNotShow->SetUrl(ui->lineEdit->text());
    if(ffmpegNotShow->Init()){
        connect(this,SIGNAL(sendSavePath(QString)),ffmpegNotShow,SLOT(getSavePath(QString)));
        if (type == 0){
            if(ui->radioS->isChecked()){  //如果按钮S被按下，则发送saveSXKSetedPath

                emit sendSavePath(saveSXKSetedPath);
                qDebug() << "保存上下客视频" << saveSXKSetedPath;
            }else{
                emit sendSavePath(saveSXKPath);
                qDebug() << "保存上下客视频" << saveSXKPath;
            }
        }
        else if (type == 1 ){
            emit sendSavePath(saveGDSXKLPath);
            qDebug() << "保存上下客视频" << saveGDSXKLPath;
        }
        else if (type == 2 ){
            emit sendSavePath(saveGDSXKRPath);
            qDebug() << "保存上下客视频" << saveGDSXKRPath;
        }
        else if (type == 3 ){
            emit sendSavePath(saveFSXKLPath);
            qDebug() << "保存上下客视频" << saveFSXKLPath;
        }
        else if (type == 4 ){
            emit sendSavePath(saveFSXKRPath);
            qDebug() << "保存上下客视频" << saveFSXKRPath;
        }

        t->start();
    }
    else{
        QMessageBox::warning(this,"Warning","ffmpeg init failed",QMessageBox::Ok);
        ui->labelVideo->clear();
    }
}

void Widget::setVideoAlreadySave()
{
    QString oldName = ui->listWidget->currentItem()->text();
    QString whichSide;

    QString startTime = ui->lineEditBegin->text();
    QString endTime = ui->lineEditEnd->text();

    if(ui->radioLR->isChecked()){
         whichSide = "Left and Right ";
    }else if(ui->radioLeft->isChecked()){
         whichSide = "Left           ";
    }else{
         whichSide = "Right          ";
    }

    QString newName = startTime + "到" + endTime + "  " + whichSide + oldName + "\n";

    QString fileName = savePathRoot + "视频信息.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qDebug() << file.errorString();
    }
    //字符转化，能够保存中文，不然用Qt自带的Latin1无法识别中文
    std::string str = newName.toStdString();
    const char* ch = str.c_str();

    file.write(ch);
    file.close();
}

void Widget::slotSeekAndStopStart()
{
    //转为时间微秒
    QString strTime =  ui->lineEditBegin->text();

    qint64 v = Helper::getTimeFromLineEdit(strTime);
    if( v == -1){
        QMessageBox::warning(this,"","上下客定位结束时间格式有误",QMessageBox::Ok);
        return;
    }
    if(v > thread->getFFmpeg()->getTotalTime()){
        QMessageBox::warning(this,"","上下客定位结束时间超出范围！",QMessageBox::Ok);
        return;
    }

    //qint64 v = (ui->lineEditBegin->text().toDouble()/1000) * (thread->getFFmpeg()->getTotalTime());
    thread->getFFmpeg()->setSeekAndSeekTime(true,v);//传入设置的value值
    //不同线程通信，为了让FFmpeg的线程再找到frame后再停下来，这里先跑500ms
    Helper::pauseMs(500);
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState){
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState){
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    Helper::pauseMs(500);
    thread->getFFmpeg()->setPause(true);
}

void Widget::slotSeekAndStopEnd()
{
    QString endTime =  ui->lineEditEnd->text();

    qint64 v = Helper::getTimeFromLineEdit(endTime);
    if( v == -1){
        QMessageBox::warning(this,"","上下客定位结束时间格式有误",QMessageBox::Ok);
        return;
    }
    if(v > thread->getFFmpeg()->getTotalTime()){
        QMessageBox::warning(this,"","上下客定位结束时间超出范围！",QMessageBox::Ok);
        return;
    }

    //qint64 v = (ui->lineEditEnd->text().toDouble()/1000) * (thread->getFFmpeg()->getTotalTime());
    thread->getFFmpeg()->setSeekAndSeekTime(true,v);//传入设置的value值
    //不同线程通信，为了让FFmpeg的线程再找到frame后再停下来，这里先跑500ms
    Helper::pauseMs(500);
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState){
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState){
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    Helper::pauseMs(500);
    thread->getFFmpeg()->setPause(true);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space  ){
        qDebug() << "Qt::Key_BackspaceQt::Key_BackspaceQt::Key_BackspaceQt::Key_BackspaceQt::Key_BackspaceQt::Key_Backspace";
        slotPlayPause();
    }

    if (ui->horizontalSlider->value()>995 || thread->getFFmpeg()->getState() == QFFmpeg::PausedState){//防止过度快进出现无法自动播放下一个视频的bug出现
        return;
    }
    if (event->key() == Qt::Key_Right){
        QString gapTimeStr = ui->lineEditSetGapTime->text();
        int gapTime = gapTimeStr.toInt();
        slotValueChanged(ui->horizontalSlider->value()+gapTime);
        qDebug() << ui->horizontalSlider->value()+10 << "Qt::Key_RightQt::Key_RightQt::Key_RightQt::Key_RightQt::Key_RightQt::Key_Right";
    }
    if ( event->key() == Qt::Key_Left){
        slotValueChanged(ui->horizontalSlider->value()-2);
        qDebug() << ui->horizontalSlider->value()-2 <<"Qt::Key_LeftQt::Key_LeftQt::Key_LeftQt::Key_LeftQt::Key_LeftQt::Key_LeftQt::Key_LeftQt::Key_Left";
    }
}

