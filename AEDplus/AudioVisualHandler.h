#ifndef AUDIOVISUALHANDLER_H
#define AUDIOVISUALHANDLER_H

#include <QObject>
#include <QMessageBox>
#include <QPushButton>
#include <functional>
#include <QLabel>
#include "HeartDisplay.h"
#include "SimulateCPR.h"
#include "PatientData.h"

/**
 * @brief AudioVisualHandler is a Singleton to ensure
 * that only a there is only a single instance
 * managing audio and vis feedback from AED
 *
 */


class AudioVisualHandler : public QObject  {
    Q_OBJECT
public:

    //  creaate singleton instance of AudioVisualHandler
    static AudioVisualHandler& getInstance() {
        static AudioVisualHandler instance;
        return instance;
    }

    // methods for displaying error messages
    void powerOnAlert(const QString&, const QString&, std::function<void()>);
    void displayCriticalAlert(const QString&);

    // for system messsage output
    void displayMsg(const QString&);
    void setMessageLabel(QLabel* label);

    void setHeartDisplay(HeartDisplay *heartDisplay);
    void changeHeartSignalDisplay(int);
    void setCPRSim(SimulateCPR *cprSim);
    void startCPR(PatientData* pt);


signals:

public slots:

private:
    explicit AudioVisualHandler();   // private singleton ctor

    QLabel* msgLabel;
    HeartDisplay *hd;
    SimulateCPR *cprSim;
};

#endif // AUDIOVISUALHANDLER_H
