#include "AudioVisualHandler.h"

AudioVisualHandler::AudioVisualHandler()
{}

void AudioVisualHandler::displayMsg(const QString& message) {
   if (msgLabel) {
           msgLabel->setText(message);
       }
}

void AudioVisualHandler::setMessageLabel(QLabel* label) {
       msgLabel = label;
   }

void AudioVisualHandler::setHeartDisplay(HeartDisplay *heartDisplay)
{
   hd = heartDisplay;
}

void AudioVisualHandler::setCPRSim(SimulateCPR *cprSim)
{
   this->cprSim = cprSim;
}

void AudioVisualHandler::startCPR(PatientData* pt)
{
   cprSim->startCPR(pt);
}

/**
* @brief AudioVisualHandler::powerOnAlert
* @param message
* @param buttonText
* @param resolveAction
*
* This method prompts the use with a pop up box when
* the device encounters an error during the self test
* process.
*
* .exec() stops program & waits for user response to
* resolve error and resume self testing process.
*/
void AudioVisualHandler::powerOnAlert(const QString& message,
                                     const QString& buttonText,
                                     std::function<void()> resolveAction) {
   QMessageBox msgBox;
   msgBox.setIcon(QMessageBox::Warning);
   msgBox.setText(message);

   // Add a custom button with the provided text
   QPushButton *resolveButton = msgBox.addButton(buttonText, QMessageBox::ActionRole);

   msgBox.exec();

   if (msgBox.clickedButton() == resolveButton) {
       // Execute the action to resolve the issue
       if (resolveAction) {
           resolveAction();
       }
   }
}

/**
* @brief AudioVisualHandler::displayCriticalAlert
* @param message
*
* Incase of AED system failure due to malfunctions in
* the ECG or CPR circuits, the device will shut down,
* and instruct respnder to call 911.
*/
void AudioVisualHandler::displayCriticalAlert(const QString& message) {
       QMessageBox msgBox;
       msgBox.setIcon(QMessageBox::Critical);
       msgBox.setWindowTitle("Critical Alert");
       msgBox.setText(message);
       msgBox.addButton(QMessageBox::Ok);
       msgBox.exec(); // pause for user response
}

void AudioVisualHandler::changeHeartSignalDisplay(int newRhythm)
{
   hd->changeRhythm(newRhythm);
}
