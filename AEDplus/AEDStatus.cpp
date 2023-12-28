#include "AEDStatus.h"

AEDStatus::AEDStatus(QObject* parent)
    : QObject(parent),
      batteryLevel(100),
      remainingCharge(45000),
      electrodesViable(true),
      electrodesConnected(false),
      deviceReady(false),
      passedSelfTest(false) {

}

// getters
int AEDStatus::getBatteryLevel() {return batteryLevel;}
int AEDStatus::getRemainingCharge() {return remainingCharge;}
bool AEDStatus::getElectrodesViability() {return electrodesViable;}
bool AEDStatus::getElectrodeConnectivity() {return electrodesConnected;}
bool AEDStatus::getCPRFunctional() {return cprFunctional;}
bool AEDStatus::getECGFunctional() {return ecgFunctional;}
bool AEDStatus::getDeviceReady() {return deviceReady;}
bool AEDStatus::getSelfTestPassed() {return passedSelfTest;}

// setters
void AEDStatus::setBatteryLevel(int level) {
    batteryLevel = level;
}
void AEDStatus::setRemainingCharge(int curCharge) {
    remainingCharge = curCharge;
}
void AEDStatus::setElectrodesViability(bool expired) {
    electrodesViable = expired;
}
void AEDStatus::setElectrodeConnectivity(bool connected) {
    electrodesConnected = connected;
}
void AEDStatus::setCPRFunction(bool function) {
    cprFunctional = function;
}
void AEDStatus::setECGFunction(bool function) {
    ecgFunctional = function;
}
void AEDStatus::setSelfTestPassed(bool passed) {
    passedSelfTest = passed;
}
void AEDStatus::setDeviceReady() {
    bool ready = getSelfTestPassed();
    deviceReady = ready;
}
