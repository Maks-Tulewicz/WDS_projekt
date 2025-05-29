/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "sideview.h"
#include "topview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout;
    QWidget *leftPanel;
    QVBoxLayout *verticalLayout_2;
    QPushButton *servoAnglesBT;
    QPushButton *animationsBT;
    QPushButton *fmServiceBT;
    QPushButton *settingsBT;
    QFrame *line;
    QStackedWidget *stackedWidget;
    QWidget *servoAnglesWD;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *servo_4_1;
    QLabel *servo_0_2;
    QLabel *servo_3_2;
    QLabel *servo_3_0;
    QLabel *servo_1_1;
    QLabel *servo_5_0;
    QLabel *noga_4_name;
    QLabel *biodro_name;
    QLabel *servo_2_0;
    QLabel *servo_0_1;
    QLabel *servo_3_1;
    QLabel *noga_3_name;
    QLabel *noga_6_name;
    QLabel *servo_1_2;
    QLabel *servo_0_0;
    QLabel *noga_1_name;
    QLabel *servo_2_2;
    QLabel *servo_4_2;
    QLabel *servo_2_1;
    QLabel *noga_2_name;
    QLabel *servo_1_0;
    QLabel *noga_5_name;
    QLabel *servo_5_2;
    QLabel *kostka_name;
    QLabel *servo_4_0;
    QLabel *kolano_name;
    QLabel *grid_filler;
    QLabel *servo_5_1;
    QWidget *settingsWD;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_settings_left;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnReconnect;
    QCheckBox *chkSimulateErrors;
    QSpacerItem *verticalSpacer;
    QLabel *languageLabel;
    QComboBox *languageComboBox;
    QFrame *line_2;
    QWidget *widget_settings_right;
    QVBoxLayout *verticalLayout_6;
    QLabel *terminalLabel;
    QPlainTextEdit *plainTextEdit;
    QWidget *animationWD;
    QHBoxLayout *horizontalLayout_2;
    QWidget *left_widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    TopView *topView;
    QFrame *workspace_devider;
    QWidget *right_widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QComboBox *comboBoxLegSide;
    SideView *sideView;
    QWidget *fMconnectionWD;
    QVBoxLayout *verticalLayout_5;
    QWidget *qualityView;
    QWidget *widget_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1104, 531);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: 686565;\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(1000, 450));
        centralwidget->setAutoFillBackground(false);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: #646c6a;\n"
""));
        horizontalLayout_6 = new QHBoxLayout(centralwidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftPanel = new QWidget(centralwidget);
        leftPanel->setObjectName(QString::fromUtf8("leftPanel"));
        leftPanel->setMinimumSize(QSize(80, 400));
        verticalLayout_2 = new QVBoxLayout(leftPanel);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        servoAnglesBT = new QPushButton(leftPanel);
        servoAnglesBT->setObjectName(QString::fromUtf8("servoAnglesBT"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/angle.png"), QSize(), QIcon::Normal, QIcon::Off);
        servoAnglesBT->setIcon(icon);
        servoAnglesBT->setIconSize(QSize(50, 50));

        verticalLayout_2->addWidget(servoAnglesBT);

        animationsBT = new QPushButton(leftPanel);
        animationsBT->setObjectName(QString::fromUtf8("animationsBT"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/motion-capture.png"), QSize(), QIcon::Normal, QIcon::Off);
        animationsBT->setIcon(icon1);
        animationsBT->setIconSize(QSize(50, 50));

        verticalLayout_2->addWidget(animationsBT);

        fmServiceBT = new QPushButton(leftPanel);
        fmServiceBT->setObjectName(QString::fromUtf8("fmServiceBT"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/antenna.png"), QSize(), QIcon::Normal, QIcon::Off);
        fmServiceBT->setIcon(icon2);
        fmServiceBT->setIconSize(QSize(50, 50));
        fmServiceBT->setCheckable(false);
        fmServiceBT->setChecked(false);

        verticalLayout_2->addWidget(fmServiceBT);

        settingsBT = new QPushButton(leftPanel);
        settingsBT->setObjectName(QString::fromUtf8("settingsBT"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        settingsBT->setIcon(icon3);
        settingsBT->setIconSize(QSize(60, 60));

        verticalLayout_2->addWidget(settingsBT);


        horizontalLayout->addWidget(leftPanel);


        horizontalLayout_6->addLayout(horizontalLayout);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMinimumSize(QSize(1, 400));
        line->setStyleSheet(QString::fromUtf8("background-color: #65d5c6"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(800, 400));
        servoAnglesWD = new QWidget();
        servoAnglesWD->setObjectName(QString::fromUtf8("servoAnglesWD"));
        horizontalLayout_4 = new QHBoxLayout(servoAnglesWD);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        widget = new QWidget(servoAnglesWD);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        servo_4_1 = new QLabel(widget);
        servo_4_1->setObjectName(QString::fromUtf8("servo_4_1"));
        servo_4_1->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_4_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_4_1, 5, 2, 1, 1);

        servo_0_2 = new QLabel(widget);
        servo_0_2->setObjectName(QString::fromUtf8("servo_0_2"));
        servo_0_2->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_0_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_0_2, 1, 3, 1, 1);

        servo_3_2 = new QLabel(widget);
        servo_3_2->setObjectName(QString::fromUtf8("servo_3_2"));
        servo_3_2->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_3_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_3_2, 4, 3, 1, 1);

        servo_3_0 = new QLabel(widget);
        servo_3_0->setObjectName(QString::fromUtf8("servo_3_0"));
        servo_3_0->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_3_0->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_3_0, 4, 1, 1, 1);

        servo_1_1 = new QLabel(widget);
        servo_1_1->setObjectName(QString::fromUtf8("servo_1_1"));
        servo_1_1->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_1_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_1_1, 2, 2, 1, 1);

        servo_5_0 = new QLabel(widget);
        servo_5_0->setObjectName(QString::fromUtf8("servo_5_0"));
        servo_5_0->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_5_0->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_5_0, 6, 1, 1, 1);

        noga_4_name = new QLabel(widget);
        noga_4_name->setObjectName(QString::fromUtf8("noga_4_name"));
        noga_4_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        noga_4_name->setTextFormat(Qt::RichText);

        gridLayout->addWidget(noga_4_name, 4, 0, 1, 1);

        biodro_name = new QLabel(widget);
        biodro_name->setObjectName(QString::fromUtf8("biodro_name"));
        biodro_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        biodro_name->setTextFormat(Qt::RichText);
        biodro_name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(biodro_name, 0, 1, 1, 1);

        servo_2_0 = new QLabel(widget);
        servo_2_0->setObjectName(QString::fromUtf8("servo_2_0"));
        servo_2_0->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_2_0->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_2_0, 3, 1, 1, 1);

        servo_0_1 = new QLabel(widget);
        servo_0_1->setObjectName(QString::fromUtf8("servo_0_1"));
        servo_0_1->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_0_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_0_1, 1, 2, 1, 1);

        servo_3_1 = new QLabel(widget);
        servo_3_1->setObjectName(QString::fromUtf8("servo_3_1"));
        servo_3_1->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_3_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_3_1, 4, 2, 1, 1);

        noga_3_name = new QLabel(widget);
        noga_3_name->setObjectName(QString::fromUtf8("noga_3_name"));
        noga_3_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        noga_3_name->setFrameShadow(QFrame::Sunken);
        noga_3_name->setTextFormat(Qt::RichText);

        gridLayout->addWidget(noga_3_name, 3, 0, 1, 1);

        noga_6_name = new QLabel(widget);
        noga_6_name->setObjectName(QString::fromUtf8("noga_6_name"));
        noga_6_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        noga_6_name->setTextFormat(Qt::RichText);

        gridLayout->addWidget(noga_6_name, 6, 0, 1, 1);

        servo_1_2 = new QLabel(widget);
        servo_1_2->setObjectName(QString::fromUtf8("servo_1_2"));
        servo_1_2->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_1_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_1_2, 2, 3, 1, 1);

        servo_0_0 = new QLabel(widget);
        servo_0_0->setObjectName(QString::fromUtf8("servo_0_0"));
        servo_0_0->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_0_0->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_0_0, 1, 1, 1, 1);

        noga_1_name = new QLabel(widget);
        noga_1_name->setObjectName(QString::fromUtf8("noga_1_name"));
        noga_1_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        noga_1_name->setTextFormat(Qt::RichText);
        noga_1_name->setScaledContents(true);
        noga_1_name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(noga_1_name, 1, 0, 1, 1);

        servo_2_2 = new QLabel(widget);
        servo_2_2->setObjectName(QString::fromUtf8("servo_2_2"));
        servo_2_2->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_2_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_2_2, 3, 3, 1, 1);

        servo_4_2 = new QLabel(widget);
        servo_4_2->setObjectName(QString::fromUtf8("servo_4_2"));
        servo_4_2->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_4_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_4_2, 5, 3, 1, 1);

        servo_2_1 = new QLabel(widget);
        servo_2_1->setObjectName(QString::fromUtf8("servo_2_1"));
        servo_2_1->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_2_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_2_1, 3, 2, 1, 1);

        noga_2_name = new QLabel(widget);
        noga_2_name->setObjectName(QString::fromUtf8("noga_2_name"));
        noga_2_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        noga_2_name->setTextFormat(Qt::RichText);

        gridLayout->addWidget(noga_2_name, 2, 0, 1, 1);

        servo_1_0 = new QLabel(widget);
        servo_1_0->setObjectName(QString::fromUtf8("servo_1_0"));
        servo_1_0->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_1_0->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_1_0, 2, 1, 1, 1);

        noga_5_name = new QLabel(widget);
        noga_5_name->setObjectName(QString::fromUtf8("noga_5_name"));
        noga_5_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        noga_5_name->setTextFormat(Qt::RichText);

        gridLayout->addWidget(noga_5_name, 5, 0, 1, 1);

        servo_5_2 = new QLabel(widget);
        servo_5_2->setObjectName(QString::fromUtf8("servo_5_2"));
        servo_5_2->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_5_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_5_2, 6, 3, 1, 1);

        kostka_name = new QLabel(widget);
        kostka_name->setObjectName(QString::fromUtf8("kostka_name"));
        kostka_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        kostka_name->setTextFormat(Qt::RichText);
        kostka_name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(kostka_name, 0, 3, 1, 1);

        servo_4_0 = new QLabel(widget);
        servo_4_0->setObjectName(QString::fromUtf8("servo_4_0"));
        servo_4_0->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_4_0->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_4_0, 5, 1, 1, 1);

        kolano_name = new QLabel(widget);
        kolano_name->setObjectName(QString::fromUtf8("kolano_name"));
        kolano_name->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        kolano_name->setTextFormat(Qt::RichText);
        kolano_name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(kolano_name, 0, 2, 1, 1);

        grid_filler = new QLabel(widget);
        grid_filler->setObjectName(QString::fromUtf8("grid_filler"));
        grid_filler->setStyleSheet(QString::fromUtf8(""));
        grid_filler->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(grid_filler, 0, 0, 1, 1);

        servo_5_1 = new QLabel(widget);
        servo_5_1->setObjectName(QString::fromUtf8("servo_5_1"));
        servo_5_1->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        servo_5_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(servo_5_1, 6, 2, 1, 1);


        horizontalLayout_4->addWidget(widget);

        stackedWidget->addWidget(servoAnglesWD);
        settingsWD = new QWidget();
        settingsWD->setObjectName(QString::fromUtf8("settingsWD"));
        horizontalLayout_3 = new QHBoxLayout(settingsWD);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget_settings_left = new QWidget(settingsWD);
        widget_settings_left->setObjectName(QString::fromUtf8("widget_settings_left"));
        widget_settings_left->setMinimumSize(QSize(400, 0));
        verticalLayout_3 = new QVBoxLayout(widget_settings_left);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btnReconnect = new QPushButton(widget_settings_left);
        btnReconnect->setObjectName(QString::fromUtf8("btnReconnect"));
        btnReconnect->setMinimumSize(QSize(0, 50));
        btnReconnect->setStyleSheet(QString::fromUtf8("color: #65d5c6;\n"
"background-color: #222;font-size: 16pt"));

        verticalLayout_3->addWidget(btnReconnect);

        chkSimulateErrors = new QCheckBox(widget_settings_left);
        chkSimulateErrors->setObjectName(QString::fromUtf8("chkSimulateErrors"));
        chkSimulateErrors->setStyleSheet(QString::fromUtf8("color: #65d5c6;font-size: 12pt"));

        verticalLayout_3->addWidget(chkSimulateErrors);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        languageLabel = new QLabel(widget_settings_left);
        languageLabel->setObjectName(QString::fromUtf8("languageLabel"));
        languageLabel->setMaximumSize(QSize(16777215, 50));
        languageLabel->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));

        verticalLayout_3->addWidget(languageLabel);

        languageComboBox = new QComboBox(widget_settings_left);
        languageComboBox->addItem(QString());
        languageComboBox->addItem(QString());
        languageComboBox->setObjectName(QString::fromUtf8("languageComboBox"));
        languageComboBox->setMinimumSize(QSize(0, 50));
        languageComboBox->setStyleSheet(QString::fromUtf8("color: #65d5c6;\n"
"background-color: #222;font-size: 16pt"));

        verticalLayout_3->addWidget(languageComboBox);


        horizontalLayout_3->addWidget(widget_settings_left);

        line_2 = new QFrame(settingsWD);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMinimumSize(QSize(8, 400));
        line_2->setStyleSheet(QString::fromUtf8("background-color: #65d5c6"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);

        widget_settings_right = new QWidget(settingsWD);
        widget_settings_right->setObjectName(QString::fromUtf8("widget_settings_right"));
        verticalLayout_6 = new QVBoxLayout(widget_settings_right);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        terminalLabel = new QLabel(widget_settings_right);
        terminalLabel->setObjectName(QString::fromUtf8("terminalLabel"));
        terminalLabel->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));

        verticalLayout_6->addWidget(terminalLabel);

        plainTextEdit = new QPlainTextEdit(widget_settings_right);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        font.setPointSize(10);
        plainTextEdit->setFont(font);
        plainTextEdit->setStyleSheet(QString::fromUtf8("\n"
"color: #65d5c6;\n"
"background-color: #222;\n"
"border: 1px solid #444;\n"
"border-radius: 3px;\n"
"padding: 3px"));
        plainTextEdit->setReadOnly(true);

        verticalLayout_6->addWidget(plainTextEdit);


        horizontalLayout_3->addWidget(widget_settings_right);

        stackedWidget->addWidget(settingsWD);
        animationWD = new QWidget();
        animationWD->setObjectName(QString::fromUtf8("animationWD"));
        horizontalLayout_2 = new QHBoxLayout(animationWD);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        left_widget = new QWidget(animationWD);
        left_widget->setObjectName(QString::fromUtf8("left_widget"));
        verticalLayout_4 = new QVBoxLayout(left_widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(left_widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 75));
        label->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        label->setTextFormat(Qt::RichText);

        verticalLayout_4->addWidget(label);

        topView = new TopView(left_widget);
        topView->setObjectName(QString::fromUtf8("topView"));

        verticalLayout_4->addWidget(topView);


        horizontalLayout_2->addWidget(left_widget);

        workspace_devider = new QFrame(animationWD);
        workspace_devider->setObjectName(QString::fromUtf8("workspace_devider"));
        workspace_devider->setMinimumSize(QSize(10, 450));
        workspace_devider->setStyleSheet(QString::fromUtf8("background-color: #65d5c6"));
        workspace_devider->setFrameShape(QFrame::VLine);
        workspace_devider->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(workspace_devider);

        right_widget = new QWidget(animationWD);
        right_widget->setObjectName(QString::fromUtf8("right_widget"));
        verticalLayout = new QVBoxLayout(right_widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(right_widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 40));
        label_2->setMaximumSize(QSize(16777215, 45));
        label_2->setStyleSheet(QString::fromUtf8("font-size: 16pt;\n"
"color: #F0822F;\n"
"background-color: #2E2E2E;\n"
"border: none;\n"
"padding: 5px;\n"
"qproperty-alignment: AlignCenter;\n"
""));
        label_2->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(label_2);

        comboBoxLegSide = new QComboBox(right_widget);
        comboBoxLegSide->addItem(QString());
        comboBoxLegSide->addItem(QString());
        comboBoxLegSide->addItem(QString());
        comboBoxLegSide->addItem(QString());
        comboBoxLegSide->addItem(QString());
        comboBoxLegSide->addItem(QString());
        comboBoxLegSide->setObjectName(QString::fromUtf8("comboBoxLegSide"));
        comboBoxLegSide->setLayoutDirection(Qt::LeftToRight);
        comboBoxLegSide->setStyleSheet(QString::fromUtf8("color: #65d5c6;\n"
"background-color: #222;"));

        verticalLayout->addWidget(comboBoxLegSide);

        sideView = new SideView(right_widget);
        sideView->setObjectName(QString::fromUtf8("sideView"));

        verticalLayout->addWidget(sideView);


        horizontalLayout_2->addWidget(right_widget);

        stackedWidget->addWidget(animationWD);
        fMconnectionWD = new QWidget();
        fMconnectionWD->setObjectName(QString::fromUtf8("fMconnectionWD"));
        verticalLayout_5 = new QVBoxLayout(fMconnectionWD);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        qualityView = new QWidget(fMconnectionWD);
        qualityView->setObjectName(QString::fromUtf8("qualityView"));

        verticalLayout_5->addWidget(qualityView);

        widget_2 = new QWidget(fMconnectionWD);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        verticalLayout_5->addWidget(widget_2);

        stackedWidget->addWidget(fMconnectionWD);

        horizontalLayout_6->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: #65d5c6"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        servoAnglesBT->setText(QString());
        animationsBT->setText(QString());
        fmServiceBT->setText(QString());
        settingsBT->setText(QString());
        servo_4_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_0_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_3_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_3_0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_1_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_5_0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        noga_4_name->setText(QCoreApplication::translate("MainWindow", "Noga 4</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        biodro_name->setText(QCoreApplication::translate("MainWindow", "BIODRO</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg_hip.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        servo_2_0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_0_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_3_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        noga_3_name->setText(QCoreApplication::translate("MainWindow", "Noga 3</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        noga_6_name->setText(QCoreApplication::translate("MainWindow", "Noga 6</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        servo_1_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_0_0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        noga_1_name->setText(QCoreApplication::translate("MainWindow", "Noga 1</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        servo_2_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_4_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        servo_2_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        noga_2_name->setText(QCoreApplication::translate("MainWindow", "Noga 2</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        servo_1_0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        noga_5_name->setText(QCoreApplication::translate("MainWindow", "Noga 5</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        servo_5_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        kostka_name->setText(QCoreApplication::translate("MainWindow", "KOSTKA</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg_ankle.png\" width=\"40\" height=\"40\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        servo_4_0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        kolano_name->setText(QCoreApplication::translate("MainWindow", "KOLANO65d5c6", nullptr));
        grid_filler->setText(QString());
        servo_5_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btnReconnect->setText(QCoreApplication::translate("MainWindow", "Po\305\202\304\205cz Ponownie", nullptr));
        chkSimulateErrors->setText(QCoreApplication::translate("MainWindow", "Symuluj B\305\202\304\231dy", nullptr));
        languageLabel->setText(QCoreApplication::translate("MainWindow", "Zmiana j\304\231zyka", nullptr));
        languageComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Polski", nullptr));
        languageComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "English", nullptr));

#if QT_CONFIG(accessibility)
        line_2->setAccessibleDescription(QCoreApplication::translate("MainWindow", "background-color: #65d5c6", nullptr));
#endif // QT_CONFIG(accessibility)
        terminalLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Top View </span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/top-view.png\" width=\"30\" height=\"30\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Side View  </span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\":/icons/robot-leg.png\" width=\"30\" height=\"30\" style=\"vertical-align:middle; margin-right: 10px;\">\n"
"<span style=\"vertical-align:middle;\">", nullptr));
        comboBoxLegSide->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        comboBoxLegSide->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        comboBoxLegSide->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));
        comboBoxLegSide->setItemText(3, QCoreApplication::translate("MainWindow", "4", nullptr));
        comboBoxLegSide->setItemText(4, QCoreApplication::translate("MainWindow", "5", nullptr));
        comboBoxLegSide->setItemText(5, QCoreApplication::translate("MainWindow", "6", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
