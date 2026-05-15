/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *modeLayout;
    QLabel *modeLabel;
    QLabel *modeValueLabel;
    QPushButton *modeButton;
    QSpacerItem *horizontalSpacer;
    QLabel *rulesTitleLabel;
    QLabel *rulesPathLabel;
    QLineEdit *inputEdit;
    QGroupBox *commitGroup;
    QVBoxLayout *verticalLayout_2;
    QLabel *commitLabel;
    QGroupBox *preeditGroup;
    QVBoxLayout *verticalLayout_3;
    QLabel *preeditLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(760, 420);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(24, 24, 24, 24);
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 22px; font-weight: 700;"));

        verticalLayout->addWidget(titleLabel);

        modeLayout = new QHBoxLayout();
        modeLayout->setObjectName("modeLayout");
        modeLabel = new QLabel(centralwidget);
        modeLabel->setObjectName("modeLabel");

        modeLayout->addWidget(modeLabel);

        modeValueLabel = new QLabel(centralwidget);
        modeValueLabel->setObjectName("modeValueLabel");
        modeValueLabel->setStyleSheet(QString::fromUtf8("font-weight: 600;"));

        modeLayout->addWidget(modeValueLabel);

        modeButton = new QPushButton(centralwidget);
        modeButton->setObjectName("modeButton");

        modeLayout->addWidget(modeButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        modeLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(modeLayout);

        rulesTitleLabel = new QLabel(centralwidget);
        rulesTitleLabel->setObjectName("rulesTitleLabel");

        verticalLayout->addWidget(rulesTitleLabel);

        rulesPathLabel = new QLabel(centralwidget);
        rulesPathLabel->setObjectName("rulesPathLabel");
        rulesPathLabel->setWordWrap(true);

        verticalLayout->addWidget(rulesPathLabel);

        inputEdit = new QLineEdit(centralwidget);
        inputEdit->setObjectName("inputEdit");

        verticalLayout->addWidget(inputEdit);

        commitGroup = new QGroupBox(centralwidget);
        commitGroup->setObjectName("commitGroup");
        verticalLayout_2 = new QVBoxLayout(commitGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        commitLabel = new QLabel(commitGroup);
        commitLabel->setObjectName("commitLabel");
        commitLabel->setMinimumSize(QSize(0, 48));
        commitLabel->setStyleSheet(QString::fromUtf8("font-size: 24px;"));
        commitLabel->setWordWrap(true);

        verticalLayout_2->addWidget(commitLabel);


        verticalLayout->addWidget(commitGroup);

        preeditGroup = new QGroupBox(centralwidget);
        preeditGroup->setObjectName("preeditGroup");
        verticalLayout_3 = new QVBoxLayout(preeditGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        preeditLabel = new QLabel(preeditGroup);
        preeditLabel->setObjectName("preeditLabel");
        preeditLabel->setMinimumSize(QSize(0, 48));
        preeditLabel->setStyleSheet(QString::fromUtf8("font-size: 24px; color: #9a3412;"));
        preeditLabel->setWordWrap(true);

        verticalLayout_3->addWidget(preeditLabel);


        verticalLayout->addWidget(preeditGroup);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 760, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ToxinKanaIME", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "ToxinKanaIME Demo", nullptr));
        modeLabel->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\250\241\345\274\217", nullptr));
        modeValueLabel->setText(QCoreApplication::translate("MainWindow", "\345\271\263\345\201\207\345\220\215", nullptr));
        modeButton->setText(QCoreApplication::translate("MainWindow", "\345\210\207\346\215\242\346\250\241\345\274\217", nullptr));
        rulesTitleLabel->setText(QCoreApplication::translate("MainWindow", "\350\247\204\345\210\231\346\226\207\344\273\266", nullptr));
        rulesPathLabel->setText(QCoreApplication::translate("MainWindow", "rules.json", nullptr));
        commitGroup->setTitle(QCoreApplication::translate("MainWindow", "Commit", nullptr));
        commitLabel->setText(QString());
        preeditGroup->setTitle(QCoreApplication::translate("MainWindow", "Preedit", nullptr));
        preeditLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
