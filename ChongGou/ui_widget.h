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
    QLineEdit *lineEditSetGDTime;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonLast;
    QPushButton *pushButtonNext;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QPushButton *pushButtonSetting;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEditSetSavePath;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioLR;
    QRadioButton *radioLeft;
    QRadioButton *radioRight;
    QRadioButton *radioS;
    QLabel *label_8;
    QLineEdit *lineEditSetGapTime;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1564, 865);
        labelVideo = new QLabel(Widget);
        labelVideo->setObjectName(QStringLiteral("labelVideo"));
        labelVideo->setGeometry(QRect(10, 10, 1261, 671));
        labelVideo->setMinimumSize(QSize(300, 310));
        labelVideo->setFocusPolicy(Qt::ClickFocus);
        labelVideo->setFrameShape(QFrame::Panel);
        labelVideo->setFrameShadow(QFrame::Sunken);
        labelVideo->setAlignment(Qt::AlignCenter);
        pushButtonOpen = new QPushButton(Widget);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(20, 790, 151, 31));
        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(1280, 40, 281, 801));
        lineEditOpen = new QLineEdit(Widget);
        lineEditOpen->setObjectName(QStringLiteral("lineEditOpen"));
        lineEditOpen->setGeometry(QRect(180, 790, 321, 31));
        lineEditSave = new QLineEdit(Widget);
        lineEditSave->setObjectName(QStringLiteral("lineEditSave"));
        lineEditSave->setGeometry(QRect(180, 830, 321, 31));
        horizontalSlider = new QSlider(Widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(21, 690, 1191, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButtonSavePicture = new QPushButton(Widget);
        pushButtonSavePicture->setObjectName(QStringLiteral("pushButtonSavePicture"));
        pushButtonSavePicture->setGeometry(QRect(260, 720, 131, 31));
        lineEditProcess = new QLineEdit(Widget);
        lineEditProcess->setObjectName(QStringLiteral("lineEditProcess"));
        lineEditProcess->setGeometry(QRect(30, 720, 71, 20));
        lineEditBegin = new QLineEdit(Widget);
        lineEditBegin->setObjectName(QStringLiteral("lineEditBegin"));
        lineEditBegin->setGeometry(QRect(450, 720, 111, 31));
        lineEditEnd = new QLineEdit(Widget);
        lineEditEnd->setObjectName(QStringLiteral("lineEditEnd"));
        lineEditEnd->setGeometry(QRect(740, 720, 121, 31));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(410, 730, 54, 12));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(720, 730, 54, 12));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 720, 51, 20));
        pushButtonDingWeiStart = new QPushButton(Widget);
        pushButtonDingWeiStart->setObjectName(QStringLiteral("pushButtonDingWeiStart"));
        pushButtonDingWeiStart->setGeometry(QRect(580, 720, 75, 23));
        pushButtonDingWeiEnd = new QPushButton(Widget);
        pushButtonDingWeiEnd->setObjectName(QStringLiteral("pushButtonDingWeiEnd"));
        pushButtonDingWeiEnd->setGeometry(QRect(870, 720, 75, 23));
        lineEditSetGDTime = new QLineEdit(Widget);
        lineEditSetGDTime->setObjectName(QStringLiteral("lineEditSetGDTime"));
        lineEditSetGDTime->setGeometry(QRect(1110, 720, 91, 31));
        pushButtonPlay = new QPushButton(Widget);
        pushButtonPlay->setObjectName(QStringLiteral("pushButtonPlay"));
        pushButtonPlay->setGeometry(QRect(824, 830, 81, 31));
        pushButtonLast = new QPushButton(Widget);
        pushButtonLast->setObjectName(QStringLiteral("pushButtonLast"));
        pushButtonLast->setGeometry(QRect(690, 830, 81, 31));
        pushButtonNext = new QPushButton(Widget);
        pushButtonNext->setObjectName(QStringLiteral("pushButtonNext"));
        pushButtonNext->setGeometry(QRect(950, 830, 81, 31));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(740, 770, 471, 31));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(670, 770, 71, 31));
        pushButtonSetting = new QPushButton(Widget);
        pushButtonSetting->setObjectName(QStringLiteral("pushButtonSetting"));
        pushButtonSetting->setGeometry(QRect(1220, 720, 51, 31));
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(960, 720, 141, 31));
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 830, 111, 31));
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(510, 760, 61, 20));
        lineEditSetSavePath = new QLineEdit(Widget);
        lineEditSetSavePath->setObjectName(QStringLiteral("lineEditSetSavePath"));
        lineEditSetSavePath->setGeometry(QRect(540, 760, 51, 21));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(261, 760, 231, 18));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioLR = new QRadioButton(layoutWidget);
        radioLR->setObjectName(QStringLiteral("radioLR"));
        radioLR->setChecked(true);

        horizontalLayout->addWidget(radioLR);

        radioLeft = new QRadioButton(layoutWidget);
        radioLeft->setObjectName(QStringLiteral("radioLeft"));

        horizontalLayout->addWidget(radioLeft);

        radioRight = new QRadioButton(layoutWidget);
        radioRight->setObjectName(QStringLiteral("radioRight"));

        horizontalLayout->addWidget(radioRight);

        radioS = new QRadioButton(layoutWidget);
        radioS->setObjectName(QStringLiteral("radioS"));

        horizontalLayout->addWidget(radioS);

        label_8 = new QLabel(Widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(80, 750, 121, 21));
        lineEditSetGapTime = new QLineEdit(Widget);
        lineEditSetGapTime->setObjectName(QStringLiteral("lineEditSetGapTime"));
        lineEditSetGapTime->setGeometry(QRect(30, 750, 51, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        labelVideo->setText(QApplication::translate("Widget", " Video Stream", 0));
        pushButtonOpen->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\350\247\206\351\242\221\350\267\257\345\276\204", 0));
        lineEditOpen->setText(QApplication::translate("Widget", "F:\\\346\234\211Bug\347\232\204\350\247\206\351\242\221", 0));
        lineEditSave->setText(QApplication::translate("Widget", "D:\\\350\247\206\351\242\221\344\277\235\345\255\230", 0));
        pushButtonSavePicture->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\350\247\206\351\242\221\346\256\265", 0));
        lineEditBegin->setText(QApplication::translate("Widget", "50-11-280", 0));
        lineEditEnd->setText(QApplication::translate("Widget", "50-21-780", 0));
        label->setText(QApplication::translate("Widget", "Begin:", 0));
        label_2->setText(QApplication::translate("Widget", "End:", 0));
        label_3->setText(QApplication::translate("Widget", "\345\210\206-\347\247\222-\346\257\253", 0));
        pushButtonDingWeiStart->setText(QApplication::translate("Widget", "\345\256\232\344\275\215", 0));
        pushButtonDingWeiEnd->setText(QApplication::translate("Widget", "\345\256\232\344\275\215", 0));
        lineEditSetGDTime->setText(QApplication::translate("Widget", "5", 0));
        pushButtonPlay->setText(QApplication::translate("Widget", "\346\232\202\345\201\234/\346\222\255\346\224\276", 0));
        pushButtonLast->setText(QApplication::translate("Widget", "\344\270\212\344\270\200\351\246\226", 0));
        pushButtonNext->setText(QApplication::translate("Widget", "\344\270\213\344\270\200\351\246\226", 0));
        label_4->setText(QApplication::translate("Widget", "\346\222\255\346\224\276\350\267\257\345\276\204\357\274\232", 0));
        pushButtonSetting->setText(QApplication::translate("Widget", "\350\256\276\347\275\256", 0));
        label_5->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\350\277\207\345\272\246\344\270\212\344\270\213\345\256\242\346\227\266\351\227\264\357\274\210s\357\274\211", 0));
        label_6->setText(QApplication::translate("Widget", "\350\247\206\351\242\221\344\277\235\345\255\230\350\267\257\345\276\204\346\240\271\347\233\256\345\275\225", 0));
        label_7->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\357\274\232", 0));
        lineEditSetSavePath->setText(QApplication::translate("Widget", "1", 0));
        radioLR->setText(QApplication::translate("Widget", "L and R", 0));
        radioLeft->setText(QApplication::translate("Widget", "L", 0));
        radioRight->setText(QApplication::translate("Widget", "R", 0));
        radioS->setText(QApplication::translate("Widget", "S", 0));
        label_8->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\345\217\263\351\224\256\345\215\203\345\210\206\346\257\224", 0));
        lineEditSetGapTime->setText(QApplication::translate("Widget", "10", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
