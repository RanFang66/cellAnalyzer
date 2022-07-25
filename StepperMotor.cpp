#include "StepperMotor.h"

StepperMotor::StepperMotor(QObject *parent) : QObject(parent)
{
    m_pos = 0;
    m_limitStatus = 0;
    m_status = 0;
    m_ser = nullptr;
}

StepperMotor::StepperMotor(int id, SerialComm* ser, QObject *parent) : QObject(parent), m_id(id), m_pos(0), m_limitStatus(0), m_status(0), m_ser(ser)
{

}

int StepperMotor::pos()
{
    return m_pos;
}

int StepperMotor::limitStatus()
{
    return m_limitStatus;
}

int StepperMotor::status()
{
    return m_status;
}

int StepperMotor::id()
{
    return m_id;
}

void StepperMotor::runForward()
{
    m_ser->sendCmd(m_id, RUN_FORWARD, 0);
}

void StepperMotor::runBackward()
{
    m_ser->sendCmd(m_id, RUN_BACKWARD, 0);
}

void StepperMotor::resetPos()
{
    m_ser->sendCmd(m_id, RESET, 0);
}

void StepperMotor::stop()
{
    m_ser->sendCmd(m_id, STOP, 0);
}

void StepperMotor::run2Pos(int pos)
{
    m_ser->sendCmd(m_id, RUN_POS, pos);
}
