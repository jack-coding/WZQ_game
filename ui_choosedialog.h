/********************************************************************************
** Form generated from reading UI file 'choosedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEDIALOG_H
#define UI_CHOOSEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chooseDialog
{
public:
    QLabel *bgLabel;
    QLabel *titleLabel;
    QWidget *layoutWidget;
    QVBoxLayout *mainvLayout;
    QLabel *chooseLab;
    QVBoxLayout *secondLayout;
    QPushButton *AImodeBtn;
    QPushButton *HumanmodeBtn;

    void setupUi(QWidget *chooseDialog)
    {
        if (chooseDialog->objectName().isEmpty())
            chooseDialog->setObjectName(QString::fromUtf8("chooseDialog"));
        chooseDialog->resize(692, 359);
        bgLabel = new QLabel(chooseDialog);
        bgLabel->setObjectName(QString::fromUtf8("bgLabel"));
        bgLabel->setGeometry(QRect(0, 0, 691, 361));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        bgLabel->setFont(font);
        bgLabel->setPixmap(QPixmap(QString::fromUtf8(":/WAQ.jpg")));
        bgLabel->setScaledContents(true);
        titleLabel = new QLabel(chooseDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(280, 30, 141, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(19);
        font1.setBold(true);
        font1.setWeight(75);
        titleLabel->setFont(font1);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setWordWrap(true);
        layoutWidget = new QWidget(chooseDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(240, 90, 211, 241));
        mainvLayout = new QVBoxLayout(layoutWidget);
        mainvLayout->setObjectName(QString::fromUtf8("mainvLayout"));
        mainvLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        mainvLayout->setContentsMargins(0, 0, 0, 0);
        chooseLab = new QLabel(layoutWidget);
        chooseLab->setObjectName(QString::fromUtf8("chooseLab"));
        chooseLab->setEnabled(true);
        chooseLab->setMaximumSize(QSize(300, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font2.setPointSize(12);
        chooseLab->setFont(font2);
        chooseLab->setTextFormat(Qt::AutoText);
        chooseLab->setAlignment(Qt::AlignCenter);

        mainvLayout->addWidget(chooseLab);

        secondLayout = new QVBoxLayout();
        secondLayout->setObjectName(QString::fromUtf8("secondLayout"));
        secondLayout->setContentsMargins(-1, 0, -1, -1);
        AImodeBtn = new QPushButton(layoutWidget);
        AImodeBtn->setObjectName(QString::fromUtf8("AImodeBtn"));
        AImodeBtn->setFont(font2);

        secondLayout->addWidget(AImodeBtn);

        HumanmodeBtn = new QPushButton(layoutWidget);
        HumanmodeBtn->setObjectName(QString::fromUtf8("HumanmodeBtn"));
        HumanmodeBtn->setFont(font2);

        secondLayout->addWidget(HumanmodeBtn);


        mainvLayout->addLayout(secondLayout);


        retranslateUi(chooseDialog);

        QMetaObject::connectSlotsByName(chooseDialog);
    } // setupUi

    void retranslateUi(QWidget *chooseDialog)
    {
        chooseDialog->setWindowTitle(QCoreApplication::translate("chooseDialog", "Form", nullptr));
        bgLabel->setText(QString());
        titleLabel->setText(QCoreApplication::translate("chooseDialog", "\344\272\224\345\255\220\346\243\213", nullptr));
        chooseLab->setText(QCoreApplication::translate("chooseDialog", "\350\257\267\351\200\211\346\213\251\346\270\270\346\210\217\346\250\241\345\274\217:", nullptr));
        AImodeBtn->setText(QCoreApplication::translate("chooseDialog", "\344\272\272\346\234\272\345\257\271\346\210\230\346\250\241\345\274\217", nullptr));
        HumanmodeBtn->setText(QCoreApplication::translate("chooseDialog", "\344\272\272\344\272\272\345\257\271\346\210\230\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chooseDialog: public Ui_chooseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEDIALOG_H
