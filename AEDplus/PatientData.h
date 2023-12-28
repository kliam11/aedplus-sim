#ifndef PATIENTDATA_H
#define PATIENTDATA_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <time.h>
#include <stdlib.h>
#include "defs.h"

#include "iostream"

using namespace std;

/**
 * @brief This class stores medical data relative to PT.
 *
 * This includes: heart rhythm data, number of shocks administered,
 * time betwee shocks, feedback during CPR. It is observable, will
 * notify the system of any changes to PT current state relevant
 * to AED functions
 *
 * *** heart rhythm sometimees abbbreviated to HR ***
 */

class PatientData : public QObject {
    Q_OBJECT

public:
    explicit PatientData(QObject *parent = nullptr);

    PatientData(int, bool, bool, int, QObject*);

    // getters for patient/shock data.
    // Get PT info
    int getAge();
    bool getHasPacemaker();
    bool getHasNonDefElectronics();
    int getHeartRhythmType();

    // Get Sys info
    bool getPadConnected();
    PadType getPadType();
    int getTimesShocked();
    QString getCPRFeedback() const;

    // Analyze Sys info
    bool getIsShockable();

    // shock + setter for shock delivered counter
    bool shock();
    void setIsShockable(bool isShockable);

    // Log CPR feedback
    void setCPRFeedback(const QString& feedback);

    // update heart rhythm data & notify observrs
    void updateHeartRhythm(int type);

    // Update pads
    bool connectPads(PadType type);
    void disconnectPads();

    string boolToString(bool);
    string padTypeToString(PadType);
    void print();

public slots:
    //void rhythmUpdatedFromCPR(int type);

signals:
    void heartRhythmUpdated(int type);

    // signal when a new shock has been delivered
    void shockDelivered();
    void updateShocksDelivered(int total);
    void updateIsShockable(bool isShockable);

    // signal to notify CPR feedback updates
    void cprFeedbackUpdated(const QString& feedback);

    void padTypeChanged(PadType type);
    void padStatusChanged(bool isConnected);

private:
    // PT info
    int age;
    bool hasPacemaker;
    bool hasNonDefElectronics;
    bool isShockable;

    /* heartRhyrhm Types (0-3)
     * 0 : Sinus Rhyrhm or PEA
     * 1 : Asyote
     * 2 : Ventricular Fibrillation (VF)
     * 3 : Ventricular Tachycardia (VT)
     */
    int heartRhythmType;

    // Sys info
    PadType currentPadType;
    bool isPadConnected = false;
    int shocksDelivered;
    QString  CPRFeedback;

    // update heart rhythm data & notify observrs

    void setShocksDelivered(int total);

    // pad type and status methods
    void setPadType(PadType type);
    void setPadStatus(bool isConnected);
};
#endif // PATIENTDATA_H
