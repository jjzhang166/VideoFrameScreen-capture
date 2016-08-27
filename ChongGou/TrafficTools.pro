#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T13:50:20
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficTools
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qffmpeg.cpp \
    playthread.cpp \
    configinfo.cpp \
    pictureutils.cpp \
    qffmpegnotshow.cpp \
    qthreadnotshow.cpp

HEADERS  += widget.h \
    qffmpeg.h \
    playthread.h \
    helper.h \
    configinfo.h \
    pictureutils.h \
    qffmpegnotshow.h \
    qthreadnotshow.h

FORMS    += widget.ui

INCLUDEPATH +=  ffmpeg/include
LIBS += ffmpeg\lib\libavcodec.dll.a \
        ffmpeg/lib/libavfilter.dll.a \
        ffmpeg/lib/libavformat.dll.a \
        ffmpeg/lib/libswscale.dll.a \
        ffmpeg/lib/libavutil.dll.a \

DESTDIR=bin
