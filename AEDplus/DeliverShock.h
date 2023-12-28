#ifndef DELIVERSHOCK_H
#define DELIVERSHOCK_H

#include "Command.h"
#include "ElectrodePad.h"
#include "AEDController.h"

/**
 * @brief Concrete Command implementation to deliver defib shock
 *
 * This class contains all steps necessary to carry out shock delivery
 * to a patient through the AED. Checks PT safety & conditions, prepares
 * AED, and administers shock in coordination with the AEDController.
 *
 * */
class DeliverShock : public Command {
public:
    DeliverShock(AEDController* controller);
    virtual ~DeliverShock() override;

    //exec shock delivery process
    virtual void execute() override;

    //check if PT can recieve shock
    virtual bool canExecute() const override;

    // debugging purposes
    virtual QString toString() const override;

private:
    AEDController* aedController;   // control ref obj
    bool shockAdvised;              // shock advisory flag
    bool passedSafetyCheck;         // pre-shock safety check flag
    int energy_charged;

    // helpers
    void performSafetyCheck();  // ensure safe shock delivery conditions
    int prepareToShock();      // prepare AED for shock delivery
    void administerShock(int energy_charged);     // administer shock to PT
};

#endif // DELIVERSHOCK_H
