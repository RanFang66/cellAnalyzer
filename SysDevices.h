#ifndef SYSDEVICES_H
#define SYSDEVICES_H

#include <QObject>
#include <StepperMotor.h>
#include <Led.h>
#include <Camera.h>
#include <SerialComm.h>

class SysDevices : public QObject
{
    Q_OBJECT
public:
    enum DEVICE_ID {
        CHIP_MOTOR = 1,
        CAMERA_MOTOR,
        FILTER_MOTOR,
        LED,
    };
    explicit SysDevices(QObject *parent = nullptr);


    SerialComm *serial() const;
    void setSerial(SerialComm *newSerial);
    StepperMotor *chipMotor() const;
    void setChipMotor(StepperMotor *newChipMotor);
    StepperMotor *cameraMotor() const;
    void setCameraMotor(StepperMotor *newCameraMotor);
    StepperMotor *filterMotor() const;
    void setFilterMotor(StepperMotor *newFilterMotor);
    Led *led() const;
    void setLed(Led *newLed);
    Camera *camera() const;
    void setCamera(Camera *newCamera);

    int chipState() const;
    void setChipState(int newChipState);

    StepperMotor *getMotor(int id);
signals:

private:
    SerialComm   *m_serial;
    StepperMotor *m_chipMotor;
    StepperMotor *m_cameraMotor;
    StepperMotor *m_filterMotor;
    Led          *m_led;
    Camera       *m_camera;
    int          m_chipState;
};

#endif // SYSDEVICES_H
