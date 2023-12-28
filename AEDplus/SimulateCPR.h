#ifndef SIMULATECPR_H
#define SIMULATECPR_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <cmath>
#include <vector>
#include "PatientData.h"

/**
 * @brief The SimulateCPR class
 *
 * Runs the CPR simulation and updates pateint data provided to it based on probabilities associated with
 * each signal type as a result of effective CPR performance
 */

class SimulateCPR: public QWidget
{
    Q_OBJECT

public:
    SimulateCPR(QWidget *parent = nullptr);
    void startCPR(PatientData* pt);

public slots:
    void handleDepth(int);
    void handlePress();
    void handleBreath();

    void handleCPRTimeUp();
    void handleSamplingTimeUp();

private:
    int CPR_COUNT                               =   0;          // total times CPR given

    static const int CPR_MAX_TIME               =   120000;     // milliseconds
    static const int SAMPLING_TIME              =   5000;       // milliseconds

    static const int MIN_PRESS_DEPTH            =   0;          // inches
    static const int MAX_PRESS_DEPTH            =   4;          // inches
    static const int BREATHS_TO_GIVE            =   2;          // breaths to be given
    static const int CYCLE_COMPRESSIONS         =   120;        // compressions to give in a cycle of CPR
    static const int COMPRESS_PER_CYCLE         =   30;
    static const int COMPRESSION_VARIANCE       =   10;         // variability in compressions/minute requirment

    PatientData* PTData;

    // [PEA, Asys, VF, VT]
    std::vector<float> rhythmProbabilities = {0.01, 0.7, 0.01, 0.01};

    QTimer cprTimer;
    QTimer samplingTimer;
    int samplingPresses;

    int depth;
    int presses;
    int breath;

    QPushButton *pressBtn;
    QPushButton *breathBtn;
    QSlider *depthSlider;
    QLabel *feedbackLabel;

    std::vector<int> pressesHistory;
    void updatePatient();
    int weightedRandom(const std::vector<float>&);
};

#endif // SIMULATECPR_H
