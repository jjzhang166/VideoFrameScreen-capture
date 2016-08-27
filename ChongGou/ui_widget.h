/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *labelVideo;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonSavePath;
    QListWidget *listWidget;
    QLineEdit *lineEditOpen;
    QLineEdit *lineEditSave;
    QSlider *horizontalSlider;
    QPushButton *pushButtonSavePicture;
    QLineEdit *lineEditProcess;
    QLineEdit *lineEditBegin;
    QLineEdit *lineEditEnd;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonDingWeiStart;
    QPushButton *pushButtonDingWeiEnd;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioLR;
    QRadioButton *radioLeft;
    QRadioButton *radioRight;
    QLineEdit *lineEditSetGDTime;
    QPushButton *pushButtonSetGDTime;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonLast;
    QPushButton *pushButtonNext;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QPushButton *pushButtonSetting;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1520, 927);
        labelVideo = new QLabel(Widget);
        labelVideo->setObjectName(QStringLiteral("labelVideo"));
        labelVideo->setGeometry(QRect(40, 20, 1301, 721));
        labelVideo->setMinimumSize(QSize(300, 310));
        labelVideo->setFrameShape(QFrame::Panel);
        labelVideo->setFrameShadow(QFrame::Sunken);
        labelVideo->setAlignment(Qt::AlignCenter);
        pushButtonOpen = new QPushButton(Widget);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(20, 850, 151, 31));
        pushButtonSavePath = new QPushButton(Widget);
        pushButtonSavePath->setObjectName(QStringLiteral("pushButtonSavePath"));
        pushButtonSavePath->setGeometry(QRect(20, 890, 151, 31));
        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(1350, 20, 161, 721));
        lineEditOpen = new QLineEdit(Widget);
        lineEditOpen->setObjectName(QStringLiteral("lineEditOpen"));
        lineEditOpen->setGeometry(QRect(180, 850, 321, 31));
        lineEditSave = new QLineEdit(Widget);
        lineEditSave->setObjectName(QStringLiteral("lineEditSave"));
        lineEditSave->setGeometry(QRect(180, 890, 321, 31));
        horizontalSlider = new QSlider(Widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(30, 750, 1281, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButtonSavePicture = new QPushButton(Widget);
        pushButtonSavePicture->setObjectName(QStringLiteral("pushButtonSavePicture"));
        pushButtonSavePicture->setGeometry(QRect(260, 780, 131, 31));
        lineEditProcess = new QLineEdit(Widget);
        lineEditProcess->setObjectName(QStringLiteral("lineEditProcess"));
        lineEditProcess->setGeometry(QRect(30, 780, 71, 20));
        lineEditBegin = new QLineEdit(Widget);
        lineEditBegin->setObjectName(QStringLiteral("lineEditBegin"));
        lineEditBegin->setGeometry(QRect(450, 780, 111, 31));
        lineEditEnd = new QLineEdit(Widget);
        lineEditEnd->setObjectName(QStringLiteral("lineEditEnd"));
        lineEditEnd->setGeometry(QRect(740, 780, 121, 31));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(410, 790, 54, 12));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(720, 790, 54, 12));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 780, 51, 20));
        pushButtonDingWeiStart = new QPushButton(Widget);
        pushButtonDingWeiStart->setObjectName(QStringLiteral("pushButtonDingWeiStart"));
        pushButtonDingWeiStart->setGeometry(QRect(580, 780, 75, 23));
        pushButtonDingWeiEnd = new QPushButton(Widget);
        pushButtonDingWeiEnd->setObjectName(QStringLiteral("pushButtonDingWeiEnd"));
        pushButtonDingWeiEnd->setGeometry(QRect(870, 780, 75, 23));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 820, 271, 18));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioLR = new QRadioButton(layoutWidget);
        radioLR->setObjectName(QStringLiteral("radioLR"));
        radioLR->setChecked(true);

        horizontalLayout_2->addWidget(radioLR);

        radioLeft = new QRadioButton(layoutWidget);
        radioLeft->setObjectName(QStringLiteral("radioLeft"));

        horizontalLayout_2->addWidget(radioLeft);

        radioRight = new QRadioButton(layoutWidget);
        radioRight->setObjectName(QStringLiteral("radioRight"));

        horizontalLayout_2->addWidget(radioRight);

        lineEditSetGDTime = new QLineEdit(Widget);
        lineEditSetGDTime->setObjectName(QStringLiteral("lineEditSetGDTime"));
        lineEditSetGDTime->setGeometry(QRect(1180, 780, 111, 31));
        pushButtonSetGDTime = new QPushButton(Widget);
        pushButtonSetGDTime->setObjectName(QStringLiteral("pushButtonSetGDTime"));
        pushButtonSetGDTime->setGeometry(QRect(1020, 780, 151, 31));
        pushButtonPlay = new QPushButton(Widget);
        pushButtonPlay->setObjectName(QStringLiteral("pushButtonPlay"));
        pushButtonPlay->setGeometry(QRect(824, 870, 81, 51));
        pushButtonLast = new QPushButton(Widget);
        pushButtonLast->setObjectName(QStringLiteral("pushButtonLast"));
        pushButtonLast->setGeometry(QRect(690, 870, 81, 51));
        pushButtonNext = new QPushButton(Widget);
        pushButtonNext->setObjectName(QStringLiteral("pushButtonNext"));
        pushButtonNext->setGeometry(QRect(950, 870, 81, 51));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(690, 830, 601, 31));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(610, 830, 71, 31));
        pushButtonSetting = new QPushButton(Widget);
        pushButtonSetting->setObjectName(QStringLiteral("pushButtonSetting"));
        pushButtonSetting->setGeometry(QRect(1350, 780, 81, 31));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        labelVideo->setText(QApplication::translate("Widget", " Video Stream", 0));
        pushButtonOpen->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\350\247\206\351\242\221\350\267\257\345\276\204", 0));
        pushButtonSavePath->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\350\247\206\351\242\221\344\277\235\345\255\230\350\267\257\345\276\204\346\240\271\347\233\256\345\275\225", 0));
        lineEditOpen->setText(QApplication::translate("Widget", "D:\\\350\247\206\351\242\221", 0));
        lineEditSave->setText(QApplication::translate("Widget", "D:\\\350\247\206\351\242\221\344\277\235\345\255\230", 0));
        pushButtonSavePicture->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\350\247\206\351\242\221\346\256\265", 0));
        lineEditBegin->setText(QApplication::translate("Widget", "00-20-500", 0));
        lineEditEnd->setText(QApplication::translate("Widget", "00-30-700", 0));
        label->setText(QApplication::translate("Widget", "Begin:", 0));
        label_2->setText(QApplication::translate("Widget", "End:", 0));
        label_3->setText(QApplication::translate("Widget", "\345\210\206-\347\247\222-\346\257\253", 0));
        pushButtonDingWeiStart->setText(QApplication::translate("Widget", "\345\256\232\344\275\215", 0));
        pushButtonDingWeiEnd->setText(QApplication::translate("Widget", "\345\256\232\344\275\215", 0));
        radioLR->setText(QApplication::translate("Widget", "L and R", 0));
        radioLeft->setText(QApplication::translate("Widget", "L", 0));
        radioRight->setText(QApplication::translate("Widget", "R", 0));
        pushButtonSetGDTime->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\350\277\207\345\272\246\344\270\212\344\270\213\345\256\242\346\227\266\351\227\264\357\274\210s\357\274\211", 0));
        pushButtonPlay->setText(QApplication::translate("Widget", "\346\232\202\345\201\234/\346\222\255\346\224\276", 0));
        pushButtonLast->setText(QApplication::translate("Widget", "\344\270\212\344\270\200\351\246\226", 0));
        pushButtonNext->setText(QApplication::translate("Widget", "\344\270\213\344\270\200\351\246\226", 0));
        label_4->setText(QApplication::translate("Widget", "\346\222\255\346\224\276\350\267\257\345\276\204\357\274\232", 0));
        pushButtonSetting->setText(QApplication::translate("Widget", "\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
