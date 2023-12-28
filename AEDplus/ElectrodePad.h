#ifndef ELECTRODEPAD_H
#define ELECTRODEPAD_H

#include <QObject>
#include <QDate>
#include "defs.h"

/**
 * @brief This class manages electrode pad functionalities.
 *
 * Handles functionalities related to the electrode pads,
 * including connectivity checks, type management (adult
 * or child), and tracking expiration.
 *
 */

class ElectrodePad : public QObject {
    Q_OBJECT

public:
    explicit ElectrodePad(QObject *parent = nullptr);

    void setPadType(PadType type);
    PadType getPadType();

    void setConnection(bool isConnected);
    bool isConnected();

    void setExpirationDate(const QDate& date);
    bool isExpired();

    // check if pads are ready for use
    // (not expired, appropriate for PT)
    bool arePadsReady();

    // collecting HR data
    void startRhythmDataCollection();
    void stopRhythmDataCollection();
    QVector<double> getCollectedRhythmData();

signals:
    // signal status changes
    void padTypeChanged(PadType type);
    void padConnectionChanged(bool isConnected);
    void padExpirationChanged(bool isExpired);
    void padReadyChanged(bool isReady);

private:
    PadType padType;
    bool connected;
    QDate expirationDate;
    double signalQuality;

    // helpers
    bool checkPadExpiration();
    bool checkPadConnection();
};

#endif // ELECTRODEPAD_H
