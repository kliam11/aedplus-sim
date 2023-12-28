#include "SimulateCPR.h"

SimulateCPR::SimulateCPR(QWidget *parent)
    : QWidget(parent), depth(0), presses(0), samplingPresses(0), breath(0)
{
    cprTimer.setInterval(CPR_MAX_TIME); // 2-min CPR timer
    samplingTimer.setInterval(SAMPLING_TIME); // sample compressions rate every 10 secs

    pressBtn = new QPushButton("PRESS CHEST");
    breathBtn = new QPushButton("GIVE BREATH");
    pressBtn->setFixedSize(100,50);
    breathBtn->setFixedSize(100,50);
    pressBtn->setStyleSheet("background-color: rgb(181, 101, 29);");
    breathBtn->setStyleSheet("background-color: lightblue;");
    pressBtn->setEnabled(false);
    breathBtn->setEnabled(false);

    depthSlider = new QSlider(Qt::Vertical);
    depthSlider->setRange(MIN_PRESS_DEPTH, MAX_PRESS_DEPTH);

    feedbackLabel = new QLabel();
    feedbackLabel->setAlignment(Qt::AlignCenter);
    QFont smallFont = feedbackLabel->font();
    smallFont.setPointSize(6);
    feedbackLabel->setFont(smallFont);
    feedbackLabel->setText("<< ---------- >>");

    QPixmap image(":/img/rsc/img/dummy.png");
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(image);
    imageLabel->setScaledContents(true);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *layoutLeft = new QVBoxLayout();
    QVBoxLayout *layoutRight = new QVBoxLayout();

    layoutLeft->addWidget(pressBtn);
    layoutLeft->addWidget(breathBtn);
    layoutLeft->addWidget(depthSlider);
    layoutLeft->addWidget(feedbackLabel);
    layoutRight->addWidget(imageLabel);
    mainLayout->addLayout(layoutLeft);
    mainLayout->addLayout(layoutRight);

    connect(pressBtn, SIGNAL(clicked()), this, SLOT(handlePress()));
    connect(breathBtn, SIGNAL(clicked()), this, SLOT(handleBreath()));
    connect(depthSlider, SIGNAL(valueChanged(int)), this, SLOT(handleDepth(int)));

    connect(&cprTimer, SIGNAL(timeout()), this, SLOT(handleCPRTimeUp()));
    connect(&samplingTimer, SIGNAL(timeout()), this, SLOT(handleSamplingTimeUp()));
}

void SimulateCPR::startCPR(PatientData* pt)
{
    PTData = pt;
    connect(PTData, SIGNAL(heartRhythmUpdated(int)), PTData, SLOT(rhythmUpdatedFromCPR(int)));

    pressBtn->setEnabled(true);

    cprTimer.start();
    samplingTimer.start();
}

void SimulateCPR::handleDepth(int d)
{
    depth = d;
}

void SimulateCPR::handlePress()
{
    presses++;
    samplingPresses++;
    if(presses>=COMPRESS_PER_CYCLE && breath<BREATHS_TO_GIVE)
    {
        breathBtn->setEnabled(true);
        pressBtn->setEnabled(false);
        feedbackLabel->setText("<< GIVE BREATH >>");
        samplingTimer.stop();
    }
}

void SimulateCPR::handleBreath()
{
    breath++;
    if(breath>=BREATHS_TO_GIVE)
    {
        breathBtn->setEnabled(false);
        presses=0;
        samplingPresses=0;
        breath=0;
        pressBtn->setEnabled(true);
        feedbackLabel->setText("<< CONTINUE COMPRESSIONS>> ");
        samplingTimer.start();
    }
}

void SimulateCPR::handleCPRTimeUp()
{
    cprTimer.stop();
    samplingTimer.stop();

    if(presses>0) CPR_COUNT++;

    presses=0;
    samplingPresses=0;
    breath=0;
    depth=0;

    pressBtn->setEnabled(false);
    breathBtn->setEnabled(false);
    depthSlider->setValue(0);

    feedbackLabel->setText("<< STOP COMPRESSIONS >>");

    updatePatient();
}

void SimulateCPR::handleSamplingTimeUp()
{
    int sampleRate = round(samplingPresses/(SAMPLING_TIME/1000));
    int extrapolatedMinuteRate = sampleRate * 60;
    pressesHistory.push_back(extrapolatedMinuteRate);

    if(extrapolatedMinuteRate > CYCLE_COMPRESSIONS+COMPRESSION_VARIANCE) {
        feedbackLabel->setText("<< SLOW DOWN >>");
    }
    else if(extrapolatedMinuteRate < CYCLE_COMPRESSIONS-COMPRESSION_VARIANCE) {
        feedbackLabel->setText("<< PRESS FASTER >>");
    }
    else if(depth<BREATHS_TO_GIVE) {
        feedbackLabel->setText("<< PUSH HARDER >>");
    }
    else if(depth>BREATHS_TO_GIVE) {
        feedbackLabel->setText("<< TOO HARD >>");
    }
    else feedbackLabel->setText("<< GOOD COMPRESSIONS >>");

    samplingPresses = 0;
}

void SimulateCPR::updatePatient()
{
    // Calculates average compression rate and assignes probability of each rhythm type resulting
    // Updates patient heart rhythm with rhythm type by weighted probability
    int rateSum = 0;
    for(unsigned long i=0; i<pressesHistory.size(); ++i){
        rateSum += pressesHistory.at(i);
    }

    int extrapolatedRateAvg = 0;
    if(pressesHistory.size()>0) extrapolatedRateAvg = round(rateSum/pressesHistory.size());

    // Update base probability of survival given CPR count (no more than about 50%)

    int newRhythm=-1;

    int shocksGiven = PTData->getTimesShocked();
    float PROBABILITY_BASE = 0;

    //Good CPR performed, heavy probability of getting one of the two shockable signals to update patient with, small chance of savinf pt
    // [PEA, Asys, VF, VT]
    if (extrapolatedRateAvg >= CYCLE_COMPRESSIONS-COMPRESSION_VARIANCE &&
            extrapolatedRateAvg <= CYCLE_COMPRESSIONS+COMPRESSION_VARIANCE) {
        if(shocksGiven > 0) { // improved base proability if shocks given
            PROBABILITY_BASE = 0.05;
            float VF = 0.25 + PROBABILITY_BASE;
            float VT = 0.25 + PROBABILITY_BASE;
            newRhythm = weightedRandom({0.2, 0.2, VF, VT});
        } else {
            newRhythm = weightedRandom({0.2, 0.3, 0.25, 0.25});
        }
    }
    //Too many compressions, small probability of patient having shockable signal
    else if (extrapolatedRateAvg > CYCLE_COMPRESSIONS+COMPRESSION_VARIANCE) {
        newRhythm = weightedRandom({0.15, 0.5, 0.175, 0.175});
    }
    //Too little compressions, near-null probability of patient having non-shockable signal
    else if (extrapolatedRateAvg <= CYCLE_COMPRESSIONS-COMPRESSION_VARIANCE && extrapolatedRateAvg > 0) {
        newRhythm = weightedRandom({0.01, 0.7, 0.095, 0.095});
    }
    // No CPR performed, patient is Asytole
    else {
        newRhythm = 1;
    }

    emit PTData->heartRhythmUpdated(newRhythm);
}

int SimulateCPR::weightedRandom(const std::vector<float>& probabilities) {
    float randomValue = static_cast<double>(rand()) / RAND_MAX;

    std::vector<double> cumulativeProbabilities;
    float cumulativeProbability = 0.0;

    for (float probability : probabilities) {
        cumulativeProbability += probability;
        cumulativeProbabilities.push_back(cumulativeProbability);
    }

    // Choose the index based on weighted probabilities
    for (size_t i = 0; i < cumulativeProbabilities.size(); ++i) {
        if (randomValue <= cumulativeProbabilities[i]) {
            return static_cast<int>(i);
        }
    }
}

