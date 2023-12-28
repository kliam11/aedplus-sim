#ifndef POWERON_H
#define POWERON_H

#include "Command.h"
#include "AEDStatus.h"
#include "AudioVisualHandler.h"

/**
 * @brief concrete command to power on AED (automatic or manual)
 *
 * Includes necessary steps required to carry out the process
 * of starting the AED: preforming self-test, init sys components
 * and setting device to ready status.
 *
 */
class PowerOn : public Command {
public:
    explicit PowerOn(AudioVisualHandler* avHandler, AEDStatus* aedStatus);
    virtual ~PowerOn() override;

    // exec  power on process
    virtual void execute() override;

    // check if AED can be powered on (enough battery power)
    virtual bool canExecute() const override;

    // debugging purposes
    virtual QString toString() const override;

private:
    AudioVisualHandler* audioVisualHandler;
    AEDStatus* aedStatus;

    // mem vars
    bool passedSelfTest;
    bool batterySufficient;
    bool electrodesConnected;
    bool cprFunctional;
    bool ecgFunctional;

    // helpers
    void performSelfTest();            // run initial self test
    void setDeviceReady();             // set AED to a ready state

    // self test components
    bool checkBatteryCapacity();
    bool checkElectrodeToAEDConnection();
    bool checkCPRFunctional();
    bool checkECGFunctional();
};


#endif // POWERON_H
