#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AEDController& aedController = AEDController::getInstance();
    AudioVisualHandler& audioVisualHandler = AudioVisualHandler::getInstance();
    aedController.setAudioVisualHandler(&audioVisualHandler);

    HeartDisplay *hd = new HeartDisplay(this);
    hd->setGeometry(750, 500, 500, 500);
    audioVisualHandler.setHeartDisplay(hd);
    ui->heartDisplay->addWidget(hd);
    audioVisualHandler.changeHeartSignalDisplay(-1);

    SimulateCPR *cprSim = new SimulateCPR(this);
    audioVisualHandler.setCPRSim(cprSim);
    ui->cprSimLayout->addWidget(cprSim);

    aedStatus = new AEDStatus(this);

    // adult PTs, no pace maker, no electronics, varying rhythms
    patients.append(new PatientData(50, false, false, 1, this));
    patients.append(new PatientData(40, false, false, 2, this));
    patients.append(new PatientData(30, false, false, 3, this));
    patients.append(new PatientData(20, false, false, 4, this));

    // adult PTs, have pace makers, no electronics, varying rhythms
    patients.append(new PatientData(55, true, false, 1, this));
    patients.append(new PatientData(45, true, false, 2, this));
    patients.append(new PatientData(35, true, false, 3, this));
    patients.append(new PatientData(25, true, false, 4, this));

    // adult PTs, no pace maker, have electronics, varying rhythms
    patients.append(new PatientData(57, false, true, 1, this));
    patients.append(new PatientData(47, false, true, 2, this));
    patients.append(new PatientData(37, false, true, 3, this));
    patients.append(new PatientData(27, false, true, 4, this));

    // adult PTs, have pace maker, have electronics, varying rhythms
    patients.append(new PatientData(51, true, true, 1, this));
    patients.append(new PatientData(41, true, true, 2, this));
    patients.append(new PatientData(31, true, true, 3, this));
    patients.append(new PatientData(21, true, true, 4, this));

    // child PTs, no pace maker, no electronics, varying rhythms
    patients.append(new PatientData(6, false, false, 1, this));
    patients.append(new PatientData(5, false, false, 2, this));
    patients.append(new PatientData(4, false, false, 3, this));
    patients.append(new PatientData(3, false, false, 4, this));

    // child PTs, have pace maker, no electronics, varying rhythms
    patients.append(new PatientData(6, true, false, 1, this));
    patients.append(new PatientData(5, true, false, 2, this));
    patients.append(new PatientData(4, true, false, 3, this));
    patients.append(new PatientData(3, true, false, 4, this));

    // child PTs, no pace maker, have electronics, varying rhythms
    patients.append(new PatientData(6, false, true, 1, this));
    patients.append(new PatientData(5, false, true, 2, this));
    patients.append(new PatientData(4, false, true, 3, this));
    patients.append(new PatientData(3, false, true, 4, this));

    // child PTs, have pace maker, have electronics, varying rhythms
    patients.append(new PatientData(6, true, true, 1, this));
    patients.append(new PatientData(5, true, true, 2, this));
    patients.append(new PatientData(4, true, true, 3, this));
    patients.append(new PatientData(3, true, true, 4, this));


    connect(ui->powerButton, SIGNAL(clicked(bool)), this, SLOT(onPowerButtonClicked()));
    connect(ui->shockButton, SIGNAL(clicked(bool)), this, SLOT(onShockButtonClicked()));

}

MainWindow::~MainWindow()
{
    qDeleteAll(patients);
    patients.clear();
    delete aedStatus;
    delete ui;

}

void MainWindow::onPowerButtonClicked() {
    AEDController& aedController = AEDController::getInstance();
    aedController.powerOn();
}

void MainWindow::onShockButtonClicked() {
    AEDController& aedController = AEDController::getInstance();
    aedController.deliverShock();
}

