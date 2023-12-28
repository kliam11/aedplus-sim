#include "InstructCPR.h"

InstructCPR::InstructCPR(AudioVisualHandler* adv, PatientData* pt)
    : audioVisHandler(adv), PTData(pt)
{}

InstructCPR::~InstructCPR()
{}

void InstructCPR::execute()
{
    if(canExecute())
    {
        audioVisHandler->startCPR(PTData);
    }
}

bool InstructCPR::canExecute() const
{
    if (PTData->getHeartRhythmType() != 0) return true;
    return false;
}

QString InstructCPR::toString() const
{
    return "CPR Instructions";
}

