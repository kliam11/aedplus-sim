#ifndef ANALYZEHEARTRHYTHM_H
#define ANALYZEHEARTRHYTHM_H

#include "Command.h"
#include "AEDController.h"
#include "PatientData.h"

/**
 * @brief Concrete Command for analyzing patient heart rhythm.
 *
 * Includes necessary steps for analyzing heart rhythm data
 * recieved from PT via AED electrodes. Ensures that analysis
 * is  preformed according to specs, coordinates with
 * AEDController to handle next steps based on analysis results.
 *
 * *** heart rhythm sometimees abbbreviated to HR *** *
 */


class AnalyzeHeartRhythm : public Command {
public:
    AnalyzeHeartRhythm(AEDController* controller, PatientData* PTData);
    virtual ~AnalyzeHeartRhythm() override;

    // exec HR process
    virtual void execute() override;

    // assess if conditions permit HR analysis
    // ex. proper electrode placement
    virtual bool canExecute() const override;

    // debugging purposes
    virtual QString toString() const override;

private:
    AEDController* aedController;
    PatientData* PTData;

    // helpers
    void analyzeRhytm();                // process HR data to determine next steps
};

#endif // ANALYZEHEARTRHYTHM_H
