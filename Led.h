#ifndef LED_H
#define LED_H

#include <QObject>
#include <SerialComm.h>

class Led : public QObject
{
    Q_OBJECT
public:
    enum LED_CMD {
        LED_RED = 1,
        LED_BLUE,
        LED_WHITE,
        LED_OFF,
    };
    explicit Led(QObject *parent = nullptr);
    explicit Led(int id, SerialComm *ser = nullptr, QObject *parent = nullptr);

    int id();
    int state();
    void setLedWhite();
    void setLedRed();
    void setLedBlue();
    void setLedOff();

signals:

private:
    int m_id;
    int m_state;
    SerialComm *m_ser;
};

#endif // LED_H
