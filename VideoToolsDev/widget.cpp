#include "widget.h"
#include "ui_widget.h"
#include "playthread.h"
#include "qffmpegnotshow.h"
#include "qthreadnotshow.h"

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
    connect(ui->pushButtonSave,SIGNAL(clicked(bool)),this,SLOT(getSavePathRoot()));
    connect(ui->pushButtonAdd,SIGNAL(clicked(bool)),this,SLOT(saveVideoPicture()));
    connect(ui->pushButtonDingWeiStart,SIGNAL(clicked(bool)),this,SLOT(seekAndStopStart()));
    connect(ui->pushButtonDingWeiEnd,SIGNAL(clicked(bool)),this,SLOT(seekAndStopEnd()));


    connect(ui->listWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(playAndSaveVideo()));
    connect(ui->pushButton1,SIGNAL(clicked(bool)),this,SLOT(playPause()));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(slotValueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setImage(const QImage &image)
{
    QPixmap pix = QPixmap::fromImage(image);
    ui->labelVideo->setPixmap(pix);
}

void Widget::on_pushButton_clicked()
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

        temp2->SetUrl(ui->lineEdit->text());
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
        QDir *dir=new QDir(openPath);
        if(dir->exists())
        {
            QStringList filter;
            QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
            ui->listWidget->clear();

            for ( int i = 0 ; i < fileInfo->length(); i++)
            {
                if (fileInfo->at(i).isFile())
                {
                    QString videoName = fileInfo->at(i).fileName();
                    qDebug() << videoName;
                    ui->listWidget->addItem(videoName);
                }
            }
            delete fileInfo;
        }
        else
        {
            QMessageBox::warning(this,"","文件夹不存在",QMessageBox::Ok);
        }
        delete dir;
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
            ui->lineEdit->setText(ui->lineEditOpen->text() + "\\" + selectedItem->text());
            QStringList list = selectedItem->text().split('.');
            QString videoName = list.at(0);//取消后缀
            saveSXKPath    = savePathRoot + "上下客样本"+"\\" + videoName + "\\" + videoName;
            saveFSXKLPath  = savePathRoot + "非上下客样本左"+"\\" + videoName + "\\" + videoName;
            saveFSXKRPath  = savePathRoot + "非上下客样本右"+"\\" + videoName + "\\" + videoName;
            saveGDSXKLPath = savePathRoot + "过度上下客样本左" +"\\" + videoName + "\\" + videoName;
            saveGDSXKRPath = savePathRoot + "过度上下客样本右" +"\\" + videoName + "\\" + videoName;
            this->on_pushButton_clicked();
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
    ui->lineEditProcess->setText(QString("%1").arg(v));
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
    qint64 SXKstartTime = (ui->lineEditBegin->text().toDouble()/1000.0)*thread->getFFmpeg()->getTotalTime();
    qint64 SXKendTime = (ui->lineEditEnd->text().toDouble()/1000.0)*thread->getFFmpeg()->getTotalTime();
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
            savePicture(GDLstartTime,GDLendTime,1);

             //得到非上下客左侧的起始时间和终止时间的long值
            qint64 FLstartTime = 0;
            qint64 FLendTime = GDLstartTime;
            savePicture(FLstartTime,FLendTime,3);
        }
        else // 如果过度上下客的开始时间小于0，就从0开始截取
        {
            savePicture(0,GDLendTime,1);
        }

        //得到过度上下客右侧的起始时间和终止时间的long值
        qint64 GDRstartTime = SXKendTime;
        qint64 GDRendTime = SXKendTime + 20000000;
        if ( GDRendTime < totalTime )
        {
//            qDebug() << "***************GDRendTime" << GDRendTime;
            savePicture(GDRstartTime,GDRendTime,2);

            //得到非上下客右侧的起始时间和终止时间的long值
            qint64 FRstartTime = GDRendTime;
            qint64 FRendTime = totalTime;
            savePicture(FRstartTime,FRendTime,4);
        }
        else// 如果过度上下客右侧的终止时间大于总时间，那么总时间就是终止时间
        {
            savePicture(GDRstartTime,totalTime,2);
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
    QString newName = "(alreadySave)"+oldName;

    QString fileName = savePathRoot + "视频信息.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        qDebug() << file.errorString();
    }
    file.write(newName.toLatin1());
    file.close();
}

void Widget::seekAndStopStart()
{
    qint64 v = (ui->lineEditBegin->text().toDouble()/1000) * (thread->getFFmpeg()->getTotalTime());
    thread->getFFmpeg()->setSeekAndSeekTime(true,v);//传入设置的value值
    //不同线程通信，为了让FFmpeg的线程再找到frame后再停下来，这里先跑500ms
    pauseMs(500);
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState)
    {
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState)
    {
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    pauseMs(500);
    thread->getFFmpeg()->setPause(true);
}

void Widget::seekAndStopEnd()
{
    qint64 v = (ui->lineEditEnd->text().toDouble()/1000) * (thread->getFFmpeg()->getTotalTime());
    thread->getFFmpeg()->setSeekAndSeekTime(true,v);//传入设置的value值
    //不同线程通信，为了让FFmpeg的线程再找到frame后再停下来，这里先跑500ms
    pauseMs(500);
    if(thread->getFFmpeg()->getState() == QFFmpeg::PlayingState)
    {
        qDebug() <<"now the state is PlayingState";
        thread->getFFmpeg()->setPause(true);
    }else if (thread->getFFmpeg()->getState() == QFFmpeg::PausedState)
    {
        qDebug() <<"now the state is PauseState";
        thread->getFFmpeg()->setPause(false);
    }
    pauseMs(500);
    thread->getFFmpeg()->setPause(true);

}

void Widget::pauseMs(int pauseTime)
{
    int time0 = QTime::currentTime().msecsSinceStartOfDay();
    int time1 = QTime::currentTime().msecsSinceStartOfDay();
    while((time1 - time0)<pauseTime)
    {
        time1 = QTime::currentTime().msecsSinceStartOfDay();
    }
}
