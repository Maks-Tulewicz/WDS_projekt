#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fmqualityview.h"
#include "servoanglemanager.h"
#include "datasimulator.h"
#include "fmqualityview.h"
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>
#include <QSizePolicy>
#include <QDebug>
#include <QTranslator>
#include <QApplication>
#include <QDirIterator>
#include <qserialport.h>
#include <QSerialPortInfo>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ----- 1) Basic button connections with tabs -----
    connect(ui->servoAnglesBT, &QPushButton::clicked,
            this, &MainWindow::showServoAngles);
    connect(ui->animationsBT, &QPushButton::clicked,
            this, &MainWindow::showAnimations);
    connect(ui->fmServiceBT, &QPushButton::clicked,
            this, &MainWindow::showConnection);
    connect(ui->settingsBT, &QPushButton::clicked,
            this, &MainWindow::showSettings);

    // ----- 2) Initialize SideView/TopView/Combo -----
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

    // ----- 5) Replace placeholder qualityView with chart -----
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

        qDebug() << "Chart connection established";
    }

    // ----- 6) Setup serial device -----
    qDebug() << "Starting serial device setup...";

    QString devicePath = "/dev/pts/10";  // NO SPACES!
    qDebug() << "Attempting to open device:" << devicePath;

    // USE QSerialPort instead of QFile
    QSerialPort *serialPort = new QSerialPort(this);
    serialPort->setPortName(devicePath);

    // Serial port configuration
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadOnly)) {
        qDebug() << "QSerialPort opened successfully!";
        qDebug() << "   - isReadable():" << serialPort->isReadable();
        qDebug() << "   - bytesAvailable():" << serialPort->bytesAvailable();

        simulator->setSerialDevice(serialPort);
        qDebug() << "Serial device set in simulator";

    } else {
        qWarning() << "Failed to open QSerialPort:" << devicePath;
        qWarning() << "   Error:" << serialPort->errorString();

        // Check available ports
        qDebug() << "Available serial ports:";
        for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
            qDebug() << "   -" << info.portName() << info.description();
        }
    }

    // ----- 7) Translator connection -----
    translator = new QTranslator(this);

    // Language change signal connection
    connect(ui->languageComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onLanguageChanged);

    // Load default language
    QString path = ":/translations/translations/hex_service_pl.qm"; // Corrected path
    if (translator->load(path)) {
        qDebug() << "Initial translation loaded successfully";
        qApp->installTranslator(translator);
    } else {
        qDebug() << "Failed to load initial translation from" << path;
    }

    setupLabels();
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
    // 1) Update QLabel table
    for (int i = 0; i < frame.angles.size(); ++i) {
        auto name = QString("servo_%1_%2").arg(i/3).arg(i%3);
        if (auto *lbl = findChild<QLabel*>(name))
            lbl->setText(QString::number(frame.angles[i], 'f', 1) + "°");
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
    frameText += QString("Time: %1 ms\n").arg(frame.timeMs);
    frameText += "Angles: [";
    for (int i = 0; i < frame.angles.size(); ++i) {
        frameText += QString::number(frame.angles[i], 'f', 1);
        if (i < frame.angles.size() - 1)
            frameText += ", ";
    }
    frameText += "]\n";
    frameText += QString("Speed: %1 pts/s\n").arg(frame.speed, 0, 'f', 1);
    frameText += QString("Packets: %1\n").arg(frame.packetCount);
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
    ui->plainTextEdit->appendPlainText("### Disconnected due to too many CRC errors ###");
    ui->btnReconnect->setEnabled(true);  // enable reconnection
}

void MainWindow::onReconnectClicked()
{
    ui->btnReconnect->setEnabled(false);
    ui->plainTextEdit->clear();

    simulator->pauseSimulation();  // First stop simulation

    QTimer::singleShot(1000, this, [this]() {  // Increase delay to 1000ms
        simulator->resetSimulation();

        QTimer::singleShot(500, this, [this]() {  // Add delay between reset and start
            simulator->startSimulation(50);  // Use original 50ms interval
            simulator->setSimulateErrors(ui->chkSimulateErrors->isChecked());
        });
    });
}

void MainWindow::loadLanguage(const QString &language)
{
    // Remove previous translation if exists
    qApp->removeTranslator(translator);

    // Load new translation
    if (translator->load(":/translations/hex_service_" + language)) {
        qApp->installTranslator(translator);
    }
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        setupLabels();
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::onLanguageChanged(int index)
{
    qDebug() << "Language change requested to index:" << index;

    // Remove previous translator
    qApp->removeTranslator(translator);

    // Load new language
    QString language = index == 0 ? "pl" : "en";
    QString path = QString(":/translations/translations/hex_service_%1.qm").arg(language); // Corrected path

    qDebug() << "Trying to load translation from:" << path;

    if (translator->load(path)) {
        qDebug() << "Translation loaded successfully";
        qApp->installTranslator(translator);
    } else {
        qDebug() << "Failed to load translation from" << path;
    }

    // Update UI
    ui->retranslateUi(this);
    setupLabels();
}

void MainWindow::setupLabels()
{
    // Set labels with icons
    ui->noga_1_name->setText(getTranslatedLabelWithIcon(tr("Noga 1"), ":/icons/robot-leg.png"));
    ui->noga_2_name->setText(getTranslatedLabelWithIcon(tr("Noga 2"), ":/icons/robot-leg.png"));
    ui->noga_3_name->setText(getTranslatedLabelWithIcon(tr("Noga 3"), ":/icons/robot-leg.png"));
    ui->noga_4_name->setText(getTranslatedLabelWithIcon(tr("Noga 4"), ":/icons/robot-leg.png"));
    ui->noga_5_name->setText(getTranslatedLabelWithIcon(tr("Noga 5"), ":/icons/robot-leg.png"));
    ui->noga_6_name->setText(getTranslatedLabelWithIcon(tr("Noga 6"), ":/icons/robot-leg.png"));

    ui->biodro_name->setText(getTranslatedLabelWithIcon(tr("BIODRO"), ":/icons/robot-leg_hip.png"));
    ui->kolano_name->setText(getTranslatedLabelWithIcon(tr("KOLANO"), ":/icons/robot-leg_knee.png"));
    ui->kostka_name->setText(getTranslatedLabelWithIcon(tr("KOSTKA"), ":/icons/robot-leg_ankle.png"));

    ui->label->setText(getTranslatedLabelWithIcon(tr("Top View"), ":/icons/top_view.png", 60, 60));
    ui->label_2->setText(getTranslatedLabelWithIcon(tr("Side View"), ":/icons/robot-leg.png", 30, 30));
}

QString MainWindow::getTranslatedLabelWithIcon(const QString& text, const QString& iconPath, int width, int height)
{
    return QString("%1</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\"%2\" width=\"%3\" height=\"%4\" style=\"vertical-align:middle; margin-right: 10px;\"><span style=\"vertical-align:middle;\">")
        .arg(text)
        .arg(iconPath)
        .arg(width)
        .arg(height);
}
