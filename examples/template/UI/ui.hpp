/********************************************************************************
** Form generated from reading UI file 'myui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_H
#define UI_H

#include <QtCore/QVariant>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helloworld
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *helloworld)
    {
        if (helloworld->objectName().isEmpty())
            helloworld->setObjectName(QStringLiteral("helloworld"));
        helloworld->resize(1080, 720);
        label = new QLabel(helloworld);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(290, 240, 311, 61));
        pushButton = new QPushButton(helloworld);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 410, 75, 23));
        pushButton_2 = new QPushButton(helloworld);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 340, 75, 23));
        pushButton_3 = new QPushButton(helloworld);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(290, 310, 75, 23));

        retranslateUi(helloworld);
        QObject::connect(pushButton, SIGNAL(released()), helloworld, SLOT(close()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), label, SLOT(hide()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), label, SLOT(show()));

        QMetaObject::connectSlotsByName(helloworld);
    } // setupUi

    void retranslateUi(QWidget *helloworld)
    {
        helloworld->setWindowTitle(QApplication::translate("helloworld", "helloworld", Q_NULLPTR));
        label->setText(QApplication::translate("helloworld", "helloworld", Q_NULLPTR));
        pushButton->setText(QApplication::translate("helloworld", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("helloworld", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("helloworld", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class helloworld: public Ui_helloworld {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_H
