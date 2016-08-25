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
#include <QtWidgets/QGroupBox>
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
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton1;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonSave;
    QListWidget *listWidget;
    QLineEdit *lineEditOpen;
    QLineEdit *lineEditSave;
    QSlider *horizontalSlider;
    QPushButton *pushButtonAdd;
    QLineEdit *lineEditProcess;
    QLineEdit *lineEditBegin;
    QLineEdit *lineEditEnd;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonDingWeiStart;
    QPushButton *pushButtonDingWeiEnd;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;

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
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(550, 840, 682, 66));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(16777215, 66));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton1 = new QPushButton(groupBox);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));

        horizontalLayout->addWidget(pushButton1);

        pushButtonOpen = new QPushButton(Widget);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(20, 850, 121, 31));
        pushButtonSave = new QPushButton(Widget);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(20, 890, 151, 31));
        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(1350, 20, 161, 721));
        lineEditOpen = new QLineEdit(Widget);
        lineEditOpen->setObjectName(QStringLiteral("lineEditOpen"));
        lineEditOpen->setGeometry(QRect(160, 849, 321, 31));
        lineEditSave = new QLineEdit(Widget);
        lineEditSave->setObjectName(QStringLiteral("lineEditSave"));
        lineEditSave->setGeometry(QRect(180, 890, 321, 31));
        horizontalSlider = new QSlider(Widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(30, 760, 1281, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButtonAdd = new QPushButton(Widget);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));
        pushButtonAdd->setGeometry(QRect(250, 790, 131, 31));
        lineEditProcess = new QLineEdit(Widget);
        lineEditProcess->setObjectName(QStringLiteral("lineEditProcess"));
        lineEditProcess->setGeometry(QRect(30, 780, 71, 20));
        lineEditBegin = new QLineEdit(Widget);
        lineEditBegin->setObjectName(QStringLiteral("lineEditBegin"));
        lineEditBegin->setGeometry(QRect(440, 790, 111, 31));
        lineEditEnd = new QLineEdit(Widget);
        lineEditEnd->setObjectName(QStringLiteral("lineEditEnd"));
        lineEditEnd->setGeometry(QRect(730, 790, 121, 31));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(400, 800, 54, 12));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(710, 800, 54, 12));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 780, 51, 20));
        pushButtonDingWeiStart = new QPushButton(Widget);
        pushButtonDingWeiStart->setObjectName(QStringLiteral("pushButtonDingWeiStart"));
        pushButtonDingWeiStart->setGeometry(QRect(570, 790, 75, 23));
        pushButtonDingWeiEnd = new QPushButton(Widget);
        pushButtonDingWeiEnd->setObjectName(QStringLiteral("pushButtonDingWeiEnd"));
        pushButtonDingWeiEnd->setGeometry(QRect(860, 790, 75, 23));
        radioButton = new QRadioButton(Widget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(1010, 800, 89, 16));
        radioButton_2 = new QRadioButton(Widget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(1120, 800, 89, 16));
        radioButton_3 = new QRadioButton(Widget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(1240, 800, 89, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        labelVideo->setText(QApplication::translate("Widget", " Video Stream", 0));
        groupBox->setTitle(QApplication::translate("Widget", "Address:", 0));
        lineEdit->setText(QApplication::translate("Widget", "E:\\1.mp4", 0));
        pushButton1->setText(QApplication::translate("Widget", "\350\277\231\346\230\257\346\222\255\346\224\276\346\232\202\345\201\234\346\214\211\351\222\256\357\274\201\344\270\215\350\246\201\351\227\256\346\210\221\344\270\272\344\273\200\344\271\210\344\274\232\345\234\250\350\277\231\351\207\214\357\274\201", 0));
        pushButtonOpen->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\350\247\206\351\242\221\350\267\257\345\276\204", 0));
        pushButtonSave->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\350\247\206\351\242\221\344\277\235\345\255\230\350\267\257\345\276\204\346\240\271\347\233\256\345\275\225", 0));
        lineEditOpen->setText(QApplication::translate("Widget", "D:\\\350\247\206\351\242\221", 0));
        lineEditSave->setText(QApplication::translate("Widget", "D:\\\350\247\206\351\242\221\344\277\235\345\255\230", 0));
        pushButtonAdd->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\350\247\206\351\242\221\346\256\265", 0));
        lineEditBegin->setText(QApplication::translate("Widget", "442", 0));
        lineEditEnd->setText(QApplication::translate("Widget", "538", 0));
        label->setText(QApplication::translate("Widget", "Begin:", 0));
        label_2->setText(QApplication::translate("Widget", "End:", 0));
        label_3->setText(QApplication::translate("Widget", "\345\215\203\345\210\206\346\257\224", 0));
        pushButtonDingWeiStart->setText(QApplication::translate("Widget", "\345\256\232\344\275\215", 0));
        pushButtonDingWeiEnd->setText(QApplication::translate("Widget", "\345\256\232\344\275\215", 0));
        radioButton->setText(QApplication::translate("Widget", "RadioButton", 0));
        radioButton_2->setText(QApplication::translate("Widget", "RadioButton", 0));
        radioButton_3->setText(QApplication::translate("Widget", "RadioButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
