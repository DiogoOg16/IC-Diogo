/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_3;
    QPushButton *connectbutton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *iplabel;
    QLineEdit *ipTextBox;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *portlabel;
    QLineEdit *portTextBox;
    QGroupBox *groupBox_2;
    QPushButton *loadDirectory;
    QComboBox *directoryBox;
    QComboBox *patientBox;
    QLabel *sujeitoLabel;
    QLabel *atividadeLabel;
    QGroupBox *groupBox;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_7;
    QLabel *labelPNG;
    QGroupBox *groupBox_6;
    QLabel *labelTipoAtividade;
    QLabel *labelAtividadeDado;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QCustomPlot *acc_widget;
    QLabel *labelPolitecnica;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout;
    QPushButton *startbutton;
    QPushButton *stopbutton;
    QPushButton *SET;
    QWidget *tab_2;
    QGroupBox *groupBox_12;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_18;
    QWidget *acc_x_widget_11;
    QGroupBox *groupBox_19;
    QWidget *gyr_z_widget_4;
    QGroupBox *groupBox_20;
    QWidget *acc_x_widget_12;
    QGroupBox *groupBox_25;
    QWidget *acc_x_widget_13;
    QGroupBox *groupBox_26;
    QWidget *acc_x_widget_15;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 1921, 1051));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1919, 1049));
        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1931, 1041));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 0, 171, 131));
        connectbutton = new QPushButton(groupBox_3);
        connectbutton->setObjectName("connectbutton");
        connectbutton->setGeometry(QRect(20, 100, 131, 21));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 30, 129, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        iplabel = new QLabel(layoutWidget);
        iplabel->setObjectName("iplabel");

        horizontalLayout->addWidget(iplabel);

        ipTextBox = new QLineEdit(layoutWidget);
        ipTextBox->setObjectName("ipTextBox");

        horizontalLayout->addWidget(ipTextBox);

        layoutWidget_2 = new QWidget(groupBox_3);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(11, 61, 141, 26));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        portlabel = new QLabel(layoutWidget_2);
        portlabel->setObjectName("portlabel");

        horizontalLayout_2->addWidget(portlabel);

        portTextBox = new QLineEdit(layoutWidget_2);
        portTextBox->setObjectName("portTextBox");

        horizontalLayout_2->addWidget(portTextBox);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(200, 0, 231, 141));
        loadDirectory = new QPushButton(groupBox_2);
        loadDirectory->setObjectName("loadDirectory");
        loadDirectory->setGeometry(QRect(30, 40, 171, 21));
        directoryBox = new QComboBox(groupBox_2);
        directoryBox->setObjectName("directoryBox");
        directoryBox->setGeometry(QRect(90, 80, 121, 21));
        patientBox = new QComboBox(groupBox_2);
        patientBox->setObjectName("patientBox");
        patientBox->setGeometry(QRect(90, 100, 121, 21));
        sujeitoLabel = new QLabel(groupBox_2);
        sujeitoLabel->setObjectName("sujeitoLabel");
        sujeitoLabel->setGeometry(QRect(10, 100, 61, 24));
        atividadeLabel = new QLabel(groupBox_2);
        atividadeLabel->setObjectName("atividadeLabel");
        atividadeLabel->setGeometry(QRect(10, 80, 71, 24));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(440, 0, 311, 181));
        plainTextEdit = new QPlainTextEdit(groupBox);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(20, 30, 271, 141));
        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(760, 0, 521, 111));
        labelPNG = new QLabel(groupBox_7);
        labelPNG->setObjectName("labelPNG");
        labelPNG->setGeometry(QRect(190, 30, 101, 71));
        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(760, 90, 431, 101));
        labelTipoAtividade = new QLabel(groupBox_6);
        labelTipoAtividade->setObjectName("labelTipoAtividade");
        labelTipoAtividade->setGeometry(QRect(20, 30, 91, 51));
        labelAtividadeDado = new QLabel(groupBox_6);
        labelAtividadeDado->setObjectName("labelAtividadeDado");
        labelAtividadeDado->setGeometry(QRect(120, 30, 301, 51));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(20, 170, 1911, 831));
        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(20, 20, 961, 391));
        acc_widget = new QCustomPlot(groupBox_5);
        acc_widget->setObjectName("acc_widget");
        acc_widget->setGeometry(QRect(9, 29, 941, 351));
        labelPolitecnica = new QLabel(tab);
        labelPolitecnica->setObjectName("labelPolitecnica");
        labelPolitecnica->setGeometry(QRect(1380, 10, 141, 21));
        layoutWidget_3 = new QWidget(tab);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(1340, 40, 211, 56));
        verticalLayout = new QVBoxLayout(layoutWidget_3);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        startbutton = new QPushButton(layoutWidget_3);
        startbutton->setObjectName("startbutton");

        verticalLayout->addWidget(startbutton);

        stopbutton = new QPushButton(layoutWidget_3);
        stopbutton->setObjectName("stopbutton");

        verticalLayout->addWidget(stopbutton);

        SET = new QPushButton(tab);
        SET->setObjectName("SET");
        SET->setGeometry(QRect(1340, 113, 221, 31));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        groupBox_12 = new QGroupBox(tab_2);
        groupBox_12->setObjectName("groupBox_12");
        groupBox_12->setGeometry(QRect(0, -100, 1911, 1131));
        layoutWidget1 = new QWidget(groupBox_12);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 100, 861, 1001));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_18 = new QGroupBox(layoutWidget1);
        groupBox_18->setObjectName("groupBox_18");
        acc_x_widget_11 = new QWidget(groupBox_18);
        acc_x_widget_11->setObjectName("acc_x_widget_11");
        acc_x_widget_11->setGeometry(QRect(9, 29, 851, 171));

        verticalLayout_2->addWidget(groupBox_18);

        groupBox_19 = new QGroupBox(layoutWidget1);
        groupBox_19->setObjectName("groupBox_19");
        gyr_z_widget_4 = new QWidget(groupBox_19);
        gyr_z_widget_4->setObjectName("gyr_z_widget_4");
        gyr_z_widget_4->setGeometry(QRect(9, 29, 911, 191));

        verticalLayout_2->addWidget(groupBox_19);

        groupBox_20 = new QGroupBox(layoutWidget1);
        groupBox_20->setObjectName("groupBox_20");
        acc_x_widget_12 = new QWidget(groupBox_20);
        acc_x_widget_12->setObjectName("acc_x_widget_12");
        acc_x_widget_12->setGeometry(QRect(0, 20, 901, 201));

        verticalLayout_2->addWidget(groupBox_20);

        groupBox_25 = new QGroupBox(layoutWidget1);
        groupBox_25->setObjectName("groupBox_25");
        acc_x_widget_13 = new QWidget(groupBox_25);
        acc_x_widget_13->setObjectName("acc_x_widget_13");
        acc_x_widget_13->setGeometry(QRect(9, 19, 901, 201));

        verticalLayout_2->addWidget(groupBox_25);

        groupBox_26 = new QGroupBox(layoutWidget1);
        groupBox_26->setObjectName("groupBox_26");
        acc_x_widget_15 = new QWidget(groupBox_26);
        acc_x_widget_15->setObjectName("acc_x_widget_15");
        acc_x_widget_15->setGeometry(QRect(9, 19, 901, 201));

        verticalLayout_2->addWidget(groupBox_26);

        tabWidget->addTab(tab_2, QString());
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Gateway config", nullptr));
        connectbutton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        iplabel->setText(QCoreApplication::translate("MainWindow", "IP:", nullptr));
        portlabel->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Dataset", nullptr));
        loadDirectory->setText(QCoreApplication::translate("MainWindow", "Load Directory", nullptr));
        sujeitoLabel->setText(QCoreApplication::translate("MainWindow", "Sujeito:", nullptr));
        atividadeLabel->setText(QCoreApplication::translate("MainWindow", "Atividade:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "LOGGER", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Dados", nullptr));
        labelPNG->setText(QString());
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Dados", nullptr));
        labelTipoAtividade->setText(QCoreApplication::translate("MainWindow", "Atividade Atual:", nullptr));
        labelAtividadeDado->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Graficos:", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "accelerator", nullptr));
        labelPolitecnica->setText(QCoreApplication::translate("MainWindow", "POLIT\303\211CNICA PUCRS", nullptr));
        startbutton->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        stopbutton->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        SET->setText(QCoreApplication::translate("MainWindow", "SET", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        groupBox_18->setTitle(QCoreApplication::translate("MainWindow", "acc_x", nullptr));
        groupBox_19->setTitle(QCoreApplication::translate("MainWindow", "acc_y", nullptr));
        groupBox_20->setTitle(QCoreApplication::translate("MainWindow", "acc_z", nullptr));
        groupBox_25->setTitle(QCoreApplication::translate("MainWindow", "gyr_x", nullptr));
        groupBox_26->setTitle(QCoreApplication::translate("MainWindow", "gyr_y", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
