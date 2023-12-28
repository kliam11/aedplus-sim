QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AEDController.cpp \
    AEDStatus.cpp \
    AnalyzeHeartRhythm.cpp \
    AudioVisualHandler.cpp \
    DeliverShock.cpp \
    HeartDisplay.cpp \
    InstructCPR.cpp \
    PatientData.cpp \
    PowerOn.cpp \
    SimulateCPR.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AEDController.h \
    AEDStatus.h \
    AnalyzeHeartRhythm.h \
    AudioVisualHandler.h \
    Command.h \
    DeliverShock.h \
    ElectrodePad.h \
    HeartDisplay.h \
    InstructCPR.h \
    PatientData.h \
    PowerOn.h \
    SimulateCPR.h \
    defs.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
