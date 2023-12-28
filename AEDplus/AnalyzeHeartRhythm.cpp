#include "AnalyzeHeartRhythm.h"

/**
 * changes made: Dec 11th, 2023, 1:30AM
 *
 * to resolve some refernece issues I assume execute()
 * will call on analyzeRhythm()
 *
 * renamed analyzeRhythm() to execute()
 * previous method state info commented respectively
 *
 * @author Zeina
 */

AnalyzeHeartRhythm::AnalyzeHeartRhythm(AEDController* controller, PatientData* PTData)
    : aedController(controller),
      PTData(PTData){
    // contructors if needed
}

AnalyzeHeartRhythm::~AnalyzeHeartRhythm() = default;

//void AnalyzeHeartRhythm::execute(){
//    analyzeRhytm();
//}

bool AnalyzeHeartRhythm::canExecute() const{
    bool padConnected = PTData->getPadConnected();
    bool padStatus = PTData->getPadConnected();

    return(padConnected & padStatus);
}


// renamed to execute(), previosuly: analyzeRhythm()
void AnalyzeHeartRhythm::execute(){
    // PatientData's heartRhythmType should be a value from 0-3.
    int heartRhythmType = PTData->getHeartRhythmType();

    switch(heartRhythmType){

    case 0:
        //case 0; heartRhythmType == 0 . PEA Heartbeat detected ( NOT-SHOCKABLE )
        aedController->getAudioVisualHandler()->changeHeartSignalDisplay(0);
        PTData->setIsShockable(false);
        break;
    case 1:
        //case 1; heartRhythmType == 1 . Asystole Heartbeat detected ( NOT-SHOCKABLE )
        aedController->getAudioVisualHandler()->changeHeartSignalDisplay(1);
        PTData->setIsShockable(false);
        break;
    case 2:
        //case 2; heartRhythmType == 2 . VF Heartbeat detected ( SHOCKABLE )
        aedController->getAudioVisualHandler()->changeHeartSignalDisplay(2);
        PTData->setIsShockable(true);
        break;
    case 3:
        //case 3; heartRhythmType == 3 . VT Heartbeat detected ( SHOCKABLE )
        aedController->getAudioVisualHandler()->changeHeartSignalDisplay(3);
        PTData->setIsShockable(true);
        break;
    default:
        //case 4; heartRhythmType is anything else.
        aedController->getAudioVisualHandler()->changeHeartSignalDisplay(-1);
        break;
    }
}



QString AnalyzeHeartRhythm::toString() const {
    return "analyzing rhythm";
}

