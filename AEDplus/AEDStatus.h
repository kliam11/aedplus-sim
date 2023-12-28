#ifndef AEDSTATUS_H
#define AEDSTATUS_H

#include <QObject>

/**
 * @brief This class contains AED device information
 *
 * Includes data members to track battery level, electrode
 * connectivity, and operational readiness. Emits signals
 * to notify other components when there are changes to
 * AED status
 *
 * updates remaining battery & charge post shock delivery
 * updates pad connection status
 * updates device readiness status
 * updates fail condition in case of self test failure
 *
 */


class AEDStatus : public QObject
{
    Q_OBJECT
public:
    explicit AEDStatus(QObject* parent = nullptr);

    int getBatteryLevel();
    void setBatteryLevel(int batteryLevel);

    bool getElectrodesViability();
    void setElectrodesViability(bool expired);

    bool getElectrodeConnectivity();
    void setElectrodeConnectivity(bool connected);

    int getRemainingCharge();
    void setRemainingCharge(int remainingCharge);

    bool getDeviceReady();
    void setDeviceReady();

    bool getSelfTestPassed();
    void setSelfTestPassed(bool passed);

    bool getCPRFunctional();
    void setCPRFunction(bool);

    bool getECGFunctional();
    void setECGFunction(bool);


private:
    int remainingCharge = 45000; // no. of jules left for shocking. (accounting for pediatric shocks. AED Guide states 225 shocks at maximum energy (200 joules)).
    int batteryLevel;   // cur estimated battery level . note : may be slightly off as division drops decimal but that will only be for appearance as remainingCharge keeps original value.
    bool electrodesViable;
    bool electrodesConnected;   // true if properly connected
    bool cprFunctional;
    bool ecgFunctional;
    bool deviceReady;   // true if passed self test
    bool passedSelfTest;
    int currentMinimumChargesRemaining = (remainingCharge/225);
};

#endif // AEDSTATUS_H
