#include "SysDevices.h"

SysDevices::SysDevices(QObject *parent) : QObject(parent)
{
    m_serial = new SerialComm(this);
    m_chipMotor = new StepperMotor(CHIP_MOTOR, m_serial, this);
    m_cameraMotor = new StepperMotor(CAMERA_MOTOR, m_serial, this);
    m_filterMotor = new StepperMotor(FILTER_MOTOR, m_serial, this);
    m_led = new Led(LED, m_serial, this);
    m_camera = new Camera(this);
}

SerialComm *SysDevices::serial() const
{
    return m_serial;
}

void SysDevices::setSerial(SerialComm *newSerial)
{
    m_serial = newSerial;
}

StepperMotor *SysDevices::chipMotor() const
{
    return m_chipMotor;
}

void SysDevices::setChipMotor(StepperMotor *newChipMotor)
{
    m_chipMotor = newChipMotor;
}

StepperMotor *SysDevices::cameraMotor() const
{
    return m_cameraMotor;
}

void SysDevices::setCameraMotor(StepperMotor *newCameraMotor)
{
    m_cameraMotor = newCameraMotor;
}

StepperMotor *SysDevices::filterMotor() const
{
    return m_filterMotor;
}

void SysDevices::setFilterMotor(StepperMotor *newFilterMotor)
{
    m_filterMotor = newFilterMotor;
}

Led *SysDevices::led() const
{
    return m_led;
}

void SysDevices::setLed(Led *newLed)
{
    m_led = newLed;
}

Camera *SysDevices::camera() const
{
    return m_camera;
}

void SysDevices::setCamera(Camera *newCamera)
{
    m_camera = newCamera;
}

int SysDevices::chipState() const
{
    return m_chipState;
}

void SysDevices::setChipState(int newChipState)
{
    m_chipState = newChipState;
}

StepperMotor *SysDevices::getMotor(int id)
{
    switch (id) {
    case CHIP_MOTOR:
        return m_chipMotor;
    case CAMERA_MOTOR:
        return m_cameraMotor;
    case FILTER_MOTOR:
        return m_filterMotor;
    default:
        return nullptr;
    }
}
