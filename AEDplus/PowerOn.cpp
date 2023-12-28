#include "PowerOn.h"
#include <QApplication>

PowerOn::PowerOn(AudioVisualHandler* avHandler, AEDStatus* aedStatus)
    : audioVisualHandler(avHandler),
      aedStatus(aedStatus),
      passedSelfTest(false),
      batterySufficient(false),
      electrodesConnected(false) {

}

PowerOn::~PowerOn() = default;

void PowerOn::execute() {
    if (canExecute()) {
        performSelfTest();
        if (passedSelfTest) {
            setDeviceReady();
        }
    } else {

    }
}

// AED will not turn on if batteries are depleted
bool PowerOn::canExecute() const {
    return batterySufficient;
}

void PowerOn::setDeviceReady() {
    aedStatus->setSelfTestPassed(true);
    aedStatus->setDeviceReady();
    audioVisualHandler->displayMsg("AED powered on and operational");
    audioVisualHandler->changeHeartSignalDisplay(1);
}



void PowerOn::performSelfTest() {

    batterySufficient = checkBatteryCapacity();
    electrodesConnected = checkElectrodeToAEDConnection();

    if (batterySufficient && electrodesConnected) {
        passedSelfTest = true;
    } else {
        passedSelfTest = false;
    }
}


// AED components functionality tests

bool PowerOn::checkBatteryCapacity() {
    int curBatteryLevel = aedStatus->getBatteryLevel();
    const int minBatteryTH = 20;
    batterySufficient = curBatteryLevel >= minBatteryTH;

    if (!batterySufficient) {
        audioVisualHandler->powerOnAlert(
            "Insufficient battery level: " + QString::number(curBatteryLevel) + "%",
            "Replace Battery",
            [this]() {
                this->aedStatus->setBatteryLevel(100);
                this->batterySufficient = true; // update batterySufficient flag
                this->performSelfTest(); // Self-test after resolving the issue
            }
        );
    }

    return batterySufficient;
}

bool PowerOn::checkElectrodeToAEDConnection() {
    if (aedStatus->getElectrodesViability()) {
        if (!aedStatus->getElectrodeConnectivity()) {
            electrodesConnected = false;
            audioVisualHandler->powerOnAlert(
                "Electrodes not connected to device",
                "Reconnect Electrodes",
                [this]() {
                    this->aedStatus->setElectrodeConnectivity(true);
                    this->performSelfTest(); // Self-test after resolving the issue
                }
            );
        } else {
            electrodesConnected = true;
        }
    } else {
        electrodesConnected = false;
        audioVisualHandler->powerOnAlert(
            "Electrodes non-viable or expired",
            "Replace Electrodes",
            [this]() {
                this->aedStatus->setElectrodesViability(true);
                this->performSelfTest(); // Self-test after resolving the issue
            }
        );
    }
    return electrodesConnected;
}

/**
 * @brief PowerOn::checkCPRFunctional
 * @return cprFunctional
 *
 * If CPR circucit malfunctions, program will terminate
 * after instructin reesponder to call 911.
 */
bool PowerOn::checkCPRFunctional() {
    if (aedStatus->getCPRFunctional()) {
        cprFunctional = true;
    } else {
        audioVisualHandler->displayCriticalAlert(
            "CPR circuit malfunction, AED not functional, call 911"
        );
        cprFunctional = false;
        QApplication::quit(); // terminate application
    }
    return cprFunctional;
}

/**
 * @brief PowerOn::checkECGFunctional
 * @return
 *
 * If ECG circucit malfunctions, program will terminate
 * after instructin reesponder to call 911.
 */
bool PowerOn::checkECGFunctional() {
    if (aedStatus->getECGFunctional()) {
        ecgFunctional = true;
    } else {
        audioVisualHandler->displayCriticalAlert(
            "ECG circuit malfunction, AED not functional, call 911"
        );
        ecgFunctional = false;
        QApplication::quit(); // Terminate the application
    }
    return ecgFunctional;
}

QString PowerOn::toString() const {
    return "Device Powered On";
}
