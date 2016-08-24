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
public slots:
        void showVideoName();
        void playAndSaveVideo();
        void getSavePathRoot();

        void playPause();
        void slotValueChanged(int value);
        void slotUpdateTime(qint64 time);
        void saveVideoPicture();
private:
    Ui::Widget *ui;
    QString savePathRoot;
    QString savePath;
    QFFmpeg *f;
    PlayThread *thread;

private slots:
    void setImage(const QImage &image);
    void on_pushButton_clicked();

signals:
    void sendSavePath(const QString savePath);
};

#endif // WIDGET_H
