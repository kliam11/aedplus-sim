#include "AEDController.h"
#include "PowerOn.h"
#include "AnalyzeHeartRhythm.h"
#include "DeliverShock.h"
#include "InstructCPR.h"

// priv ctor
AEDController::AEDController(QObject* parent)
    : QObject(parent),
      curStatus(new AEDStatus()),
      elecPad(nullptr),
      curPTData(new PatientData())  {

}

void AEDController::powerOn() {
    PowerOn* powerOnCmd = new PowerOn(&AudioVisualHandler::getInstance(),
                                      this->curStatus);
    powerOnCmd->execute();
}

void AEDController::deliverShock() {
    DeliverShock* deliverShockCmd = new DeliverShock(this);
    deliverShockCmd->execute();
}

void AEDController::analyzeHeartRhythm() {
    AnalyzeHeartRhythm* analyzeHRCmd = new AnalyzeHeartRhythm(this, this->curPTData);
    analyzeHRCmd->execute();
}

void AEDController::instructCPR() {
    InstructCPR* instructCPRCmd = new InstructCPR(&AudioVisualHandler::getInstance(), this->curPTData);
    instructCPRCmd->execute();
}
PatientData& AEDController::getPatientData() {
    return *curPTData;
}

AEDStatus& AEDController::getAEDStatus(){
    return *curStatus;
    }

void AEDController::setAudioVisualHandler(AudioVisualHandler* handler)
{
    audioVisualHandler = handler;
}

AudioVisualHandler* AEDController::getAudioVisualHandler()
{
    return audioVisualHandler;
}
