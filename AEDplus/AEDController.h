#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QString>
#include "Command.h"
#include "PatientData.h"
#include "AEDStatus.h"
#include "ElectrodePad.h"
#include "AudioVisualHandler.h"

/**
 * @brief This control class is a singleton managing the
 * states and operations of the AED
 *
 * It receives input from the user and patient data, determines
 * the appropriate command to execute, and maintains the current
 * state of the AED system. It also handles transitions between
 * different operational states, such as powering on, analyzing
 * heart rhythms, delivering shocks, and providing CPR instructions.
 *
 */

class AEDController : public QObject {
    Q_OBJECT

public:
    // singleton instance of AEDController
    static AEDController& getInstance() {
        static AEDController instance;
        return instance;
    }

    // commands
    void powerOn();
    void analyzeHeartRhythm();
    void deliverShock();
    void instructCPR();

    // updates battery
    void updateAEDStatus(const AEDStatus& status);

    // return current PatientData object
    PatientData& getPatientData();
    //return current AEDStatus
    AEDStatus& getAEDStatus();

    void setAudioVisualHandler(AudioVisualHandler*);
    AudioVisualHandler* getAudioVisualHandler();

private:
    // priavte ctor - singleton pattern
    explicit AEDController(QObject* parent = nullptr);

    // mem vars
    AEDStatus* curStatus;
    QMap<QString, Command*> commands; // maps cmd names to instances
    ElectrodePad* elecPad;
    PatientData* curPTData;
    AudioVisualHandler *audioVisualHandler;
};

#endif // AEDCONTROLLER_H
