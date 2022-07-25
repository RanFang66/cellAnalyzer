QT       += core gui serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Camera.cpp \
    CellAnalyzer.cpp \
    ExperiSettings.cpp \
    Led.cpp \
    QDlgLogin.cpp \
    QFormExperiData.cpp \
    QFormUserManage.cpp \
    QWdgtDebug.cpp \
    SerialComm.cpp \
    StepperMotor.cpp \
    SysDevices.cpp \
    UserManage.cpp \
    main.cpp \
    QmwCellAnalyzer.cpp

HEADERS += \
    Camera.h \
    CellAnalyzer.h \
    ExperiSettings.h \
    Led.h \
    QDlgLogin.h \
    QFormExperiData.h \
    QFormUserManage.h \
    QWdgtDebug.h \
    QmwCellAnalyzer.h \
    SerialComm.h \
    StepperMotor.h \
    SysDevices.h \
    UserManage.h \
    toupcam.h

FORMS += \
    QDlgLogin.ui \
    QFormExperiData.ui \
    QFormUserManage.ui \
    QWdgtDebug.ui \
    QmwCellAnalyzer.ui

TRANSLATIONS += \
    CellAnalyzer_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

INCLUDEPATH += $$PWD/. \
               /usr/local/include/opencv4/. \
               /usr/local/include/opencv4/opencv2/.

DEPENDPATH += $$PWD/.

LIBS += -L$$PWD -ltoupcam \
        /usr/local/lib/libopencv*
