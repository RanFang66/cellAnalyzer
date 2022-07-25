#include "SerialComm.h"

SerialComm::SerialComm(QObject *parent) : QSerialPort(parent)
{
    m_serNum = 0;
}

bool SerialComm::connect()
{
    if (updateSerInfo() > 0) {
        setPort(m_serInfo.at(0));
        setBaudRate(QSerialPort::Baud115200);
        setDataBits(QSerialPort::Data8);
        setParity(QSerialPort::NoParity);
        setStopBits(QSerialPort::OneStop);
        setFlowControl(QSerialPort::NoFlowControl);
        if (open(QIODevice::ReadWrite)){
            return true;
        }
    }
    return false;
}

bool SerialComm::sendCmd(int dev, int cmd, int data)
{
    char sendBuff[9];
    int sum = 0;
    qint64 ret = 0;

    sendBuff[0] = (char)0x58;
    sendBuff[1] = (char)0x59;
    sendBuff[2] = (char)(dev & 0x000000FF);
    sendBuff[3] = (char)(cmd & 0x000000FF);
    sendBuff[7] = (char)(data & 0x000000FF);
    sendBuff[6] = (char)((data & 0x0000FF00) >> 8);
    sendBuff[5] = (char)((data & 0x00FF0000) >> 16);
    sendBuff[4] = (char)((data & 0xFF000000) >> 24);
    for (int i = 2; i < 8; i++) {
        sum += sendBuff[i];
    }
    sendBuff[8] = sum & 0x000000FF;

    ret = writeData(sendBuff, 9);

    emit writeDataOk(sendBuff, ret);

    return (ret == 9);
}

int SerialComm::updateSerInfo()
{
    m_serInfo.clear();
    m_serInfo = QSerialPortInfo::availablePorts();
    m_serNum = m_serInfo.length();

    return m_serNum;
}

const QList<QSerialPortInfo> &SerialComm::serInfo() const
{
    return m_serInfo;
}


