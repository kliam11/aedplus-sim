#include <iostream>
#include <string>
#include "DeliverShock.h"
#include "PatientData.h"
#include "AEDController.h"

DeliverShock::DeliverShock(AEDController* controller)
    : aedController(controller),
      shockAdvised(false),
      passedSafetyCheck(false) {
  //constructor
}
DeliverShock::~DeliverShock() {
  //destructor for future
}

void DeliverShock::execute() {
  shockAdvised = aedController->getPatientData().getIsShockable();
  performSafetyCheck();
  if(canExecute()){
    energy_charged = prepareToShock();
    administerShock(energy_charged);
  } else {
  // abort, operater canceled the shock.
}
}

bool DeliverShock::canExecute() const{
  return(shockAdvised && passedSafetyCheck);
}

void DeliverShock::performSafetyCheck(){
    PatientData& patientData = aedController->getPatientData();
    bool hasPacemaker = patientData.getHasPacemaker();
    bool hasNonDefElectronics = patientData.getHasNonDefElectronics();
    bool padConnected = patientData.getPadConnected();
  passedSafetyCheck = (!(hasPacemaker) && !(hasNonDefElectronics) && padConnected);

}

int DeliverShock::prepareToShock(){
  int energy = 0;
  // depending on type of electrode attached and amount of times shocked, charge up a different amount of electricity.
  // adult shock values are 120j/150j/200j
  // child  shock values are 50j/70j/85j
  PatientData& patientData = aedController->getPatientData();
  PadType padType = patientData.getPadType();
  int timesShocked = patientData.getTimesShocked();
  if(padType == PadType::Adult){
  // Adult Electrode Connected
    if(timesShocked >= 2){
      energy+= 200;
    }
    else{
      energy+= 120+(timesShocked*30);
    }
  }
  else{
  // Pediatric Electrode Connected
    if(timesShocked >= 2){
      energy+= 85;
    }
    else{
      energy+= 50+(timesShocked*20);
    }
  }
  return energy;
}
void DeliverShock::administerShock(int energy_charged){
  aedController->deliverShock();
  AEDStatus& aedStatus = aedController->getAEDStatus();{}
  if(aedStatus.getBatteryLevel() >= 0 || aedStatus.getRemainingCharge() >= 70){
    int battery = aedStatus.getRemainingCharge();
    battery -= energy_charged;
    aedStatus.setRemainingCharge(battery);
    aedStatus.setBatteryLevel((battery/2)/225);
    aedController->getPatientData().shock();
    passedSafetyCheck = false;
    }
}


QString DeliverShock::toString() const {
    return "shock deliveredd";
}
