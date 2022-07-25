#include "QWdgtDebug.h"
#include "ui_QWdgtDebug.h"
#include <QDebug>
#include <QMessageBox>
#include <opencv.hpp>
#include <imgproc.hpp>
#include <QSet>

QWdgtDebug::QWdgtDebug(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QWdgtDebug)
{
    ui->setupUi(this);

    autoFocusTimer = new QTimer(this);
    autoFocusTimer->setInterval(500);
    autoFocusTimer->stop();
    clarityTbl.clear();
    currCamPos = 0;
    focusPos = 0;

    connect(autoFocusTimer, SIGNAL(timeout()), this, SLOT(on_autoFocusTimer_timeout()));
}

QWdgtDebug::~QWdgtDebug()
{
    delete ui;
}

void QWdgtDebug::on_btnRefreshPortInfo_clicked()
{
    ui->comboPortName->clear();
    if (dev->serial()->updateSerInfo() > 0) {
        foreach (QSerialPortInfo info, dev->serial()->serInfo()) {
            ui->comboPortName->addItem(info.portName());
        }
    }
}


void QWdgtDebug::on_btnSerialConnect_clicked(bool checked)
{
    if (checked) {
        if (dev->serial()->connect()) {
            qDebug() << "Serial Port Open Ok.";
            ui->btnSerialConnect->setText("Disconnect");
        } else {
            ui->btnSerialConnect->setChecked(false);
            QMessageBox::warning(this, "Failed", "Open Serial Port Failed");
        }
    } else {
        dev->serial()->close();
        ui->btnSerialConnect->setText("Connect");
    }
}


void QWdgtDebug::on_btnMotoRunForward_clicked()
{
    motor->runForward();
}


void QWdgtDebug::on_comboMotoType_currentIndexChanged(int index)
{
    motor = dev->getMotor(index+1);
}


void QWdgtDebug::on_btnSetMotoSpeed_clicked()
{
    motor->stop();
}


void QWdgtDebug::on_btnMotoRunBackward_clicked()
{
    motor->runBackward();
}


void QWdgtDebug::on_btnMotoStop_clicked()
{
    motor->stop();
}


void QWdgtDebug::on_btnMotoReset_clicked()
{
    motor->resetPos();
}


void QWdgtDebug::on_btnMotoSteps_clicked()
{
    motor->run2Pos(ui->editMotoRunSteps->text().toInt());
}

void QWdgtDebug::on_ledChanged()
{
    if (ui->radioLedRed->isChecked()) {
        dev->led()->setLedRed();
    } else if (ui->radioLedBlue->isChecked()) {
        dev->led()->setLedBlue();
    } else if (ui->radioLedWhite->isChecked()) {
        dev->led()->setLedWhite();
    } else {
        dev->led()->setLedOff();
    }
}


void QWdgtDebug::on_btnOpenCam_clicked(bool checked)
{
    if (checked) {
        if (dev->camera()->open()) {
            ui->btnOpenCam->setText("Close");
            ui->lblCamName->setText(dev->camera()->cameraName());
            qDebug() << "Open Camera Ok";
        } else {
            ui->btnOpenCam->setChecked(false);
            QMessageBox::warning(this, "Failed", "Open Camera Failed!");
        }
    } else {
        ui->lblCamName->setText("Camera Closed");
        dev->camera()->close();
        ui->btnOpenCam->setText("Open");
    }
}


void QWdgtDebug::on_btnStartCam_clicked(bool checked)
{
    if (checked) {
        if (dev->camera()->startPicture()) {
            ui->btnStartCam->setText("Stop");
            qDebug() << "Camera Start Operating";
        } else {
            QMessageBox::warning(this, "Failed", "Start Camera Failed!");
            ui->btnStartCam->setChecked(false);
        }
    } else {
        dev->camera()->stopPicture();
        ui->btnStartCam->setText("Open");
    }
}


void QWdgtDebug::on_cBoxAutoExposure_clicked(bool checked)
{
    dev->camera()->setAutoExpo(checked);
}


void QWdgtDebug::on_btnWbOnce_clicked()
{
    dev->camera()->WhiteBalanceOnce();
}

double getLaplacian(Mat &img)
{
    Mat sobelImg;
    cv::cvtColor(img, sobelImg, COLOR_BGR2BGRA);
    cv::Laplacian(sobelImg, sobelImg, CV_8U);

    double meanVal;

    meanVal = mean(sobelImg)[0];

    return meanVal;
}




void QWdgtDebug::on_autoFocusTimer_timeout()
{
    Mat img = dev->camera()->getImage();

    clarityTbl.insert(currCamPos, getLaplacian(img));
    updateImgShow(img);
    double maxClarity;


    ui->progressAutoFocus->setValue(currCamPos / 10);
    currCamPos += 20;
    if (currCamPos > 1000) {
        foreach (double val, clarityTbl.values()) {
            if (val > maxClarity) {
                maxClarity = val;
            }
        }
        focusPos = clarityTbl.key(maxClarity);
        dev->cameraMotor()->run2Pos(focusPos);
        autoFocusTimer->stop();
        currCamPos = 0;
        ui->btnAutoFocus->setChecked(false);
    } else {
        dev->cameraMotor()->run2Pos(currCamPos);
    }
}

void QWdgtDebug::on_btnAutoFocus_clicked(bool checked)
{
    if (checked) {
        ui->progressAutoFocus->setValue(0);
        autoFocusTimer->start(500);
    } else {
        autoFocusTimer->stop();
        ui->progressAutoFocus->setValue(0);
        clarityTbl.clear();
        currCamPos = 0;
    }
}

void QWdgtDebug::on_camera_imageUpdated()
{
    updateImgShow(dev->camera()->getImage());
}

void QWdgtDebug::setDev(SysDevices *newDev)
{
    dev = newDev;
    motor = dev->getMotor(1);
}

void QWdgtDebug::updateImgShow(Mat img)
{
    cv::resize(img, img, cv::Size(img.cols/4, img.rows/4), 0.3, 0,3);
    QImage imgShow(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    ui->lblImage->setPixmap(QPixmap::fromImage(imgShow));
    ui->lblImage->setScaledContents(true);
}


void QWdgtDebug::on_btnRefresh_clicked(bool checked)
{
    if (checked) {
        connect(this->dev->camera(), SIGNAL(imageUpdated()), this, SLOT(on_camera_imageUpdated()));
    } else {
        disconnect(this->dev->camera(), SIGNAL(imageUpdated()), this, SLOT(on_camera_imageUpdated()));
    }
}

