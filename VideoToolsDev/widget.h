#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qffmpeg.h"
#include "playthread.h"
#include <QImage>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void resetQFFmpeg();
    void keyPressEvent(QKeyEvent  *event);
    //保存上下客图片 type=0是上下客 1是过度上下客left 2是过度上下客right 3 非上下客left 4非上下客right
    void savePicture(qint64 startTime,qint64 endTime,int type);

    void setVideoAlreadySave();
    void pauseMs(int pauseTime);
public slots:
        void showVideoName();
        void playAndSaveVideo();
        void getSavePathRoot();

        void playPause();
        void slotValueChanged(int value);
        void slotUpdateTime(qint64 time);
        void saveVideoPicture();
        void seekAndStopStart();
        void seekAndStopEnd();
private:
    Ui::Widget *ui;
    QString savePathRoot;
    QString saveSXKPath; //保存上下课的路径
    QString saveFSXKLPath;//保存非上下课left的路径
    QString saveFSXKRPath;//保存非上下课right的路径
    QString saveGDSXKLPath;//保存过度上left下课的路径
    QString saveGDSXKRPath;//保存过度上right下课的路径
    QFFmpeg *f;
    PlayThread *thread;

private slots:
    void setImage(const QImage &image);
    void on_pushButton_clicked();

signals:
    void sendSavePath(const QString savePath);
};

#endif // WIDGET_H
