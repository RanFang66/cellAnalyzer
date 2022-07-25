#include "Led.h"

Led::Led(QObject *parent) : QObject(parent), m_id(0), m_state(0), m_ser(nullptr)
{

}

Led::Led(int id, SerialComm *ser, QObject *parent) : QObject(parent), m_id(id), m_state(0), m_ser(ser)
{

}

int Led::id()
{
    return m_id;
}

int Led::state()
{
    return m_state;
}

void Led::setLedWhite()
{
    m_ser->sendCmd(m_id, LED_WHITE, 0);
}

void Led::setLedRed()
{
    m_ser->sendCmd(m_id, LED_RED, 0);
}

void Led::setLedBlue()
{
    m_ser->sendCmd(m_id, LED_BLUE, 0);
}

void Led::setLedOff()
{
    m_ser->sendCmd(m_id, LED_OFF, 0);
}
