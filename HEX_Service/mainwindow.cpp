#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QRandomGenerator>
#include<QDebug>

ServoAngleManager* servoManager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("HEX_Service");
    connect(ui->fmServiceBT, &QPushButton::clicked, this, &MainWindow::showConnection);
    connect(ui->animationsBT, &QPushButton::clicked, this, &MainWindow::showAnimations);
    connect(ui->servoAnglesBT, &QPushButton::clicked, this, &MainWindow::showServoAngles);
    connect(ui->settingsBT, &QPushButton::clicked, this, &MainWindow::showSettings);

    // mainwindow.cpp
    //sideView = new SideView(this);
    //ui->verticalLayout->addWidget(sideView);  // Dodaj widget do layoutu



    // mainwindow.cpp
    connect(ui->comboBoxLegSide, SIGNAL(currentIndexChanged(int)),
            sideView, SLOT(setActiveLeg(int)));

    servoManager = new ServoAngleManager(this);

    // Rejestracja wszystkich QLabeli
    for (int leg = 0; leg < 6; ++leg) {
        for (int joint = 0; joint < 3; ++joint) {
            QString objName = QString("servo_%1_%2").arg(leg).arg(joint);
            QLabel* label = findChild<QLabel*>(objName);
            if (label) {
                servoManager->registerLabel(leg, joint, label);
            }
        }
    }
    // Inicjalizacja DataSimulator
    simulator = new DataSimulator(this);
    connect(simulator, &DataSimulator::frameReady, this, &MainWindow::updateServoGUI);

    // Ładowanie danych z pliku
    if (!simulator->loadData("servo_test_data.txt")) {
        qWarning() << "Nie udało się załadować danych!";
    }

    // Rozpoczęcie symulacji
    simulator->startSimulation(50);  // Symulacja co 1000 ms (1 sekunda)



    // // Test: ustaw losowe kąty


    // for (int leg = 0; leg < 6; ++leg) {
    //     for (int joint = 0; joint < 3; ++joint) {
    //         float fakeAngle = static_cast<float>(
    //             QRandomGenerator::global()->bounded(30, 151) // 151 → bo górny zakres jest wykluczony
    //             );

    //          // losowy kąt 30–150
    //         servoManager->setAngle(leg, joint, fakeAngle);
    //     }
    // }




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAnimations() {
    ui->stackedWidget->setCurrentWidget(ui->animationWD);
}

void MainWindow::showServoAngles() {
    ui->stackedWidget->setCurrentWidget(ui->servoAnglesWD);
}

void MainWindow::showConnection() {
    ui->stackedWidget->setCurrentWidget(ui->fMconnectionWD);
}

void MainWindow::showSettings() {
    ui->stackedWidget->setCurrentWidget(ui->settingsWD);
}
void MainWindow::updateServoGUI(const ServoFrame &frame)
{
\

    int legIdx = ui->comboBoxLegSide->currentIndex();
    Q_ASSERT(frame.angles.size() >= 18);
    if (!sideView || !topView) return;
    int leg = ui->comboBoxLegSide->currentIndex();
    Q_ASSERT(leg>=0 && leg<6);
    int off    = legIdx * 3;




    sideView->setJointAngles(frame.angles[off+1], frame.angles[off+2]);

    for (int i = 0; i < 6; ++i)
        topView->setHipAngle(i, frame.angles[i*3]);

    // aktualizacja QLabeli
    for (int i = 0; i < frame.angles.size(); ++i) {
        if (auto *lbl = findChild<QLabel*>(QString("servo_%1_%2").arg(i/3).arg(i%3)))
            lbl->setText(QString::number(frame.angles[i], 'f', 1) + u8"°");
    }
}
// Slot zmieniający aktywną nogę w sideView
void MainWindow::onLegSelectionChanged(int index)
{
    if (index >= 0 && index < 6) {
        sideView->setActiveLeg(index);  // Zmieniamy aktywną nogę w widoku sideView
    }
}
