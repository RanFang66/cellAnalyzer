#ifndef QWDGTDEBUG_H
#define QWDGTDEBUG_H

#include <QWidget>
#include "SysDevices.h"
#include <QTimer>
#include <QMessageBox>
#include <QMap>

namespace Ui {
class QWdgtDebug;
}

class QWdgtDebug : public QWidget
{
    Q_OBJECT

public:
    explicit QWdgtDebug(QWidget *parent = nullptr);
    ~QWdgtDebug();

    void autoFocus();

    void setDev(SysDevices *newDev);

private slots:
    void on_btnRefreshPortInfo_clicked();

    void on_btnSerialConnect_clicked(bool checked);

    void on_btnMotoRunForward_clicked();

    void on_comboMotoType_currentIndexChanged(int index);

    void on_btnSetMotoSpeed_clicked();

    void on_btnMotoRunBackward_clicked();

    void on_btnMotoStop_clicked();

    void on_btnMotoReset_clicked();

    void on_btnMotoSteps_clicked();

    void on_ledChanged();

    void on_btnOpenCam_clicked(bool checked);

    void on_btnStartCam_clicked(bool checked);

    void on_cBoxAutoExposure_clicked(bool checked);

    void on_btnWbOnce_clicked();

    void on_autoFocusTimer_timeout();

    void on_btnAutoFocus_clicked(bool checked);

    void on_camera_imageUpdated();

    void on_btnRefresh_clicked(bool checked);

private:
    Ui::QWdgtDebug *ui;
    SysDevices *dev;
    StepperMotor *motor;

    QTimer *autoFocusTimer;

    QMap<int, double> clarityTbl;
    int currCamPos;
    int focusPos;

    void updateImgShow(Mat img);
};

#endif // QWDGTDEBUG_H
