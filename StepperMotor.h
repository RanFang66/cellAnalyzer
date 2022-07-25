#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <QObject>
#include "SerialComm.h"

class StepperMotor : public QObject
{
    Q_OBJECT
public:
    enum MOTOR_CMD {
        RUN_POS = 0,
        STOP,
        RUN_FORWARD,
        RUN_BACKWARD,
        RESET,
        SET_SPEED,
    };

    explicit StepperMotor(QObject *parent = nullptr);
    explicit StepperMotor(int id, SerialComm *ser = nullptr, QObject *parent = nullptr);

    int pos();
    int limitStatus();
    int status();
    int id();

    void runForward();
    void runBackward();
    void resetPos();
    void stop();
    void run2Pos(int pos);
signals:

private:
    int m_id;
    int m_pos;
    int m_limitStatus;
    int m_status;

    SerialComm *m_ser;
};

#endif // STEPPERMOTOR_H
