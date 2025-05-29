#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fmqualityview.h"
#include "servoanglemanager.h"
#include "datasimulator.h"
#include"fmqualityview.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>
#include <QSizePolicy>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ----- 1) Podstawowe połączenia przycisków z zakładkami -----
    connect(ui->servoAnglesBT, &QPushButton::clicked,
            this, &MainWindow::showServoAngles);
    connect(ui->animationsBT, &QPushButton::clicked,
            this, &MainWindow::showAnimations);
    connect(ui->fmServiceBT, &QPushButton::clicked,
            this, &MainWindow::showConnection);
    connect(ui->settingsBT, &QPushButton::clicked,
            this, &MainWindow::showSettings);

    // ----- 2) Inicjalizacja SideView/TopView/Combo -----
    sideView = ui->sideView;
    topView  = ui->topView;
    connect(ui->comboBoxLegSide, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onLegSelectionChanged);

    // ----- 3) ServoAngleManager -----
    servoManager = new ServoAngleManager(this);
    for (int leg = 0; leg < 6; ++leg) {
        for (int joint = 0; joint < 3; ++joint) {
            auto name = QString("servo_%1_%2").arg(leg).arg(joint);
            if (auto *lbl = findChild<QLabel*>(name))
                servoManager->registerLabel(leg, joint, lbl);
        }
    }

    // ----- 4) DataSimulator -----
    simulator = new DataSimulator(this);
    connect(simulator, &DataSimulator::frameReady,
            this,      &MainWindow::updateServoGUI);
    connect(simulator, &DataSimulator::logError, this, &MainWindow::logError);
    connect(ui->chkSimulateErrors, &QCheckBox::stateChanged, this, [=](int){
        simulator->setSimulateErrors(ui->chkSimulateErrors->isChecked());
    });
    connect(simulator, &DataSimulator::logError, this, &MainWindow::handleLogError);
    connect(simulator, &DataSimulator::logMessage, this, &MainWindow::handleLogMessage);
    connect(simulator, &DataSimulator::disconnectedDueToErrors, this, &MainWindow::onSimDisconnect);
    connect(ui->btnReconnect, &QPushButton::clicked, this, &MainWindow::onReconnectClicked);






    // ----- 5) Podmień placeholder qualityView na wykres -----
    {
        QWidget *ph = ui->qualityView;
        QLayout *lyt = ph->parentWidget()->layout();
        lyt->removeWidget(ph);
        delete ph;
        auto *qualityView = findChild<FmQualityView*>("qualityView");


        auto *chart = new FmQualityView(this);
        chart->setObjectName("qualityView");
        chart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        lyt->addWidget(chart);

        connect(simulator, &DataSimulator::qualitySample,
                chart,     &FmQualityView::addMeasurement);
    }

    // ----- 6) Start symulacji -----
    if (!simulator->loadData(QStringLiteral("servo_test_data.txt")))
        qWarning() << "Nie udało się załadować danych!";
    simulator->startSimulation(50);
    logToTerminal("System uruchomiony.\nGotowy do działania.");
    simulator->setSimulateErrors(ui->chkSimulateErrors->isChecked());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showServoAngles() {
    ui->stackedWidget->setCurrentWidget(ui->servoAnglesWD);
}
void MainWindow::showAnimations() {
    ui->stackedWidget->setCurrentWidget(ui->animationWD);
}
void MainWindow::showConnection() {
    ui->stackedWidget->setCurrentWidget(ui->fMconnectionWD);
}
void MainWindow::showSettings() {
    ui->stackedWidget->setCurrentWidget(ui->settingsWD);
}

void MainWindow::onLegSelectionChanged(int index)
{
    sideView->setActiveLeg(index);
}

void MainWindow::updateServoGUI(const ServoFrame &frame)
{
    // 1) Aktualizacja tabelki QLabel
    for (int i = 0; i < frame.angles.size(); ++i) {
        auto name = QString("servo_%1_%2").arg(i/3).arg(i%3);
        if (auto *lbl = findChild<QLabel*>(name))
            lbl->setText(QString::number(frame.angles[i], 'f', 1) + u8"°");
    }
    // 2) TopView
    for (int leg = 0; leg < 6; ++leg) {
        float hip = frame.angles[leg*3 + 0];
        topView->setHipAngle(leg, hip - 90.0f);
    }
    // 3) SideView
    int legIdx = ui->comboBoxLegSide->currentIndex();
    float knee  = frame.angles[legIdx*3 + 1];
    float ankle = frame.angles[legIdx*3 + 2];
    sideView->setJointAngles(knee, ankle);


    QString frameText;
    frameText += QString("Czas: %1 ms\n").arg(frame.timeMs);
    frameText += "Kąty: [";
    for (int i = 0; i < frame.angles.size(); ++i) {
        frameText += QString::number(frame.angles[i], 'f', 1);
        if (i < frame.angles.size() - 1)
            frameText += ", ";
    }
    frameText += "]\n";
    frameText += QString("Prędkość: %1 pkt/s\n").arg(frame.speed, 0, 'f', 1);
    frameText += QString("Pakiety: %1\n").arg(frame.packetCount);
    frameText += "---------------------------";

    logToTerminal(frameText);


}

void MainWindow::logToTerminal(const QString &message) {
    // ui->plainTextEdit->appendPlainText(message);
}
void MainWindow::logError(const QString &msg) {
    ui->plainTextEdit->appendPlainText("[ERROR] " + msg);
}
void MainWindow::handleLogError(const QString &msg) {
    ui->plainTextEdit->appendHtml("<span style='color:red;'>" + msg + "</span>");
}


void MainWindow::handleLogMessage(const QString &msg) {
    // Limit the number of messages stored in plainTextEdit
    static const int MAX_LINES = 1000;
    QPlainTextEdit* editor = ui->plainTextEdit;

    if (editor->document()->lineCount() > MAX_LINES) {
        QTextCursor cursor(editor->document());
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor,
                            editor->document()->lineCount() - MAX_LINES);
        cursor.removeSelectedText();
    }
    editor->appendPlainText(msg);
}

void MainWindow::onSimDisconnect()
{
    ui->plainTextEdit->appendPlainText("### Rozłączono z powodu zbyt wielu błędów CRC ###");
    ui->btnReconnect->setEnabled(true);  // umożliwiamy ponowne połączenie
}


void MainWindow::onReconnectClicked()
{
    ui->btnReconnect->setEnabled(false);
    ui->plainTextEdit->clear();

    simulator->pauseSimulation();  // Najpierw zatrzymaj symulację

    QTimer::singleShot(1000, this, [this]() {  // Zwiększ opóźnienie do 1000ms
        simulator->resetSimulation();

        QTimer::singleShot(500, this, [this]() {  // Dodaj opóźnienie między resetem a startem
            simulator->startSimulation(50);  // Użyj oryginalnego interwału 50ms
            simulator->setSimulateErrors(ui->chkSimulateErrors->isChecked());
        });
    });
}


