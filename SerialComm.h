#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QSerialPort>
#include <QSerialPortInfo>

class SerialComm : public QSerialPort
{
    Q_OBJECT
public:
    explicit SerialComm(QObject *parent = nullptr);

    bool connect();
    bool sendCmd(int dev, int cmd, int data);
    int  updateSerInfo();


    const QList<QSerialPortInfo> &serInfo() const;

signals:
    void writeDataOk(char *data, int len);

private:
    QList<QSerialPortInfo> m_serInfo;
    int    m_serNum;
};

#endif // SERIALCOMM_H
