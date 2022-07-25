#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <toupcam.h>
#include <opencv.hpp>

using namespace cv;
#define IMAGE_WIDTH     1360
#define IMAGE_HEIGHT    1024

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);

    bool checkCamera();
    bool open();
    bool startPicture();
    bool stopPicture();
    void close();
    Mat  getImage();
    QString cameraName();

    bool WhiteBalanceOnce();

    bool setAutoExpo(bool enable);

signals:
    void imageUpdated();
private:
    ToupcamDeviceV2     m_curDev;
    HToupcam            m_hToupcam;
    uchar               *m_pData;
    ToupcamFrameInfoV2  m_imgInfo;
    int                 m_width;
    int                 m_height;
    Mat m_image;

    static void eventCallback(unsigned nEvent, void *pCallBackCtx);
    void handleImageCallback(void);
};

#endif // CAMERA_H
