#ifndef INSTRUCTCPR_H
#define INSTRUCTCPR_H

#include "Command.h"
#include "AudioVisualHandler.h"

/**
 * @brief concrete command for providing CPR instuctions
 *
 * Includes logic required to instruct rescuer in preforming
 * CPR when prompted. Contains info pretaining to compression
 * rate, depth, and breaths, adhering to AED admin guide.
 *
 */
class InstructCPR : public Command
{
public:
    explicit InstructCPR(AudioVisualHandler*, PatientData*);
    virtual ~InstructCPR() override;

    // start giving cpr intructions
    virtual void execute() override;

    // determines if CPR pre-conditions allow CPR on PTT
    virtual bool canExecute() const override;

    // debugging purposes
    virtual QString toString() const override;

private:
    //AudioVisualHandler* audioVisHandler;
    //PatientData* PTData;
    AudioVisualHandler* audioVisHandler;
    PatientData* PTData;

};

#endif // INSTRUCTCPR_H
