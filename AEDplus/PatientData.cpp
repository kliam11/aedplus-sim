#include "PatientData.h"

PatientData::PatientData(QObject* parent)
    : QObject(parent) {

}

PatientData::PatientData(int a, bool p, bool e, int t, QObject* parent)
    : QObject(parent),
      age(a),
      hasPacemaker(p),
      hasNonDefElectronics(e),
      heartRhythmType(t) {
    if(heartRhythmType < 0 || heartRhythmType > 3){
        heartRhythmType = 0;
    }
    isPadConnected = false;
    shocksDelivered = 0;
    CPRFeedback = "";
    isShockable = false;

}

// getters for patient/shock data.
// Get PT info
int PatientData::getAge() { return age; }
bool PatientData::getHasPacemaker() { return hasPacemaker; }
bool PatientData::getHasNonDefElectronics() { return hasNonDefElectronics; }
int PatientData::getHeartRhythmType() { return heartRhythmType; }


// Get Sys info
bool PatientData::getPadConnected() { return isPadConnected; }
PadType PatientData::getPadType() { return currentPadType; }
int PatientData::getTimesShocked() { return shocksDelivered;}
QString PatientData::getCPRFeedback() const {return CPRFeedback;}


// Analyze Sys info
bool PatientData::getIsShockable() { return isShockable; }

// shock + setter for shock delivered counter
bool PatientData::shock()
{
    if(isPadConnected) {
        shockDelivered();
        setShocksDelivered(getTimesShocked() + 1);
        return true;
    }
    return false;
}
void PatientData::setIsShockable(bool shockable){
    isShockable = shockable;
    updateIsShockable(isShockable);
}

// Log CPR feedback
void PatientData::setCPRFeedback(const QString &feedback) {CPRFeedback = feedback;}

// update heart rhythm data & notify observrs
void PatientData::updateHeartRhythm(int type) {
    if( type<0 || type > 3){
        return; // invalid type
    }
    heartRhythmType = type;
    heartRhythmUpdated(type);
}

// Update pads
bool PatientData::connectPads(PadType type)
{
    if(getPadConnected()) {
        return false;
    }
    setPadType(type);
    setPadStatus(true);
    return true;
}
void PatientData::disconnectPads() { setPadStatus(false); }

string PatientData::boolToString(bool b)
{
    if(b){
        return "true";
    }
    return "false";
}

string PatientData::padTypeToString(PadType)
{
    if(getPadType() == PadType::Adult) {
        return "Adult";
    }
    else if(getPadType() == PadType::Pediatric) {
        return "Pediatric";
    }
    else {
        return "Invalid Type";
    }
}

void PatientData::print() {
    cout << "******* PT info *******" << endl;
    cout << "Age: " << getAge() << endl;
    cout << "hassPacemaker: " << boolToString(getHasPacemaker()) << endl;
    cout << "hasNonDefElectronics: " << boolToString(getHasNonDefElectronics()) << endl;
    cout << "HeartRythmType: " << getHeartRhythmType() << endl;
    cout << "isPadConnected: " << boolToString(getPadConnected()) << endl;
    if(getPadConnected()) {
        cout << "padType: " << padTypeToString(getPadType()) << endl;;
    }
    cout << "timesShocked: " << getTimesShocked() << endl;
    // getCPRFeedback
    cout << "isShockable: " << boolToString(getIsShockable()) << endl;;
    cout << endl;
    return;
}

// PRIVATE


// pad type and status methods
void PatientData::setPadType(PadType type) {
    if(type != PadType::Adult && type != PadType::Pediatric) {
        return; // invalid type
    }
    currentPadType = type;
    padTypeChanged(currentPadType);
}

void PatientData::setShocksDelivered(int total){
   shocksDelivered = total;
   updateShocksDelivered(shocksDelivered);
}

void PatientData::setPadStatus(bool isConnected) {
    isPadConnected = isConnected;
    padStatusChanged(isPadConnected);
}

