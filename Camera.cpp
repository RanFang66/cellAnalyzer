#include "Camera.h"

Camera::Camera(QObject *parent) : QObject(parent), m_hToupcam(nullptr), m_width(IMAGE_WIDTH), m_height(IMAGE_HEIGHT)
{

}

bool Camera::checkCamera()
{
    int camNum = 0;
    ToupcamDeviceV2  allDevs[TOUPCAM_MAX];

    camNum = Toupcam_EnumV2(allDevs);
    if (camNum > 0) {
        m_curDev = allDevs[0];
        return true;
    }
    return false;
}

bool Camera::open()
{
    if (checkCamera()) {
        if ((m_hToupcam = Toupcam_Open(m_curDev.id))) {
            Toupcam_get_Size(m_hToupcam, &m_width, &m_height);
            return true;
        }
    }
    return false;
}

bool Camera::startPicture()
{
    HRESULT ret = 0;
    Toupcam_StartPullModeWithCallback(m_hToupcam, eventCallback, this);
    if (SUCCEEDED(ret)) {
        m_pData = new uchar[TDIBWIDTHBYTES(m_width * 24) * m_height];
    }
    return SUCCEEDED(ret);
}

bool Camera::stopPicture()
{
    HRESULT ret = 0;
    ret = Toupcam_Stop(m_hToupcam);
    if (SUCCEEDED(ret)) {
        delete [] m_pData;
        m_pData = nullptr;
    }
    return SUCCEEDED(ret);
}

void Camera::close()
{
    if (m_hToupcam != nullptr) {
        stopPicture();
        Toupcam_Close(m_hToupcam);
        m_hToupcam = nullptr;
    }
}

Mat Camera::getImage()
{
    return m_image;
}

QString Camera::cameraName()
{
    return QString(m_curDev.displayname);
}

bool Camera::WhiteBalanceOnce()
{
    HRESULT ret = 0;

    ret = Toupcam_AwbOnce(m_hToupcam, NULL, NULL);

    return SUCCEEDED(ret);
}

bool Camera::setAutoExpo(bool enable)
{
    HRESULT ret = 0;

    ret = Toupcam_put_AutoExpoEnable(m_hToupcam, enable);

    return SUCCEEDED(ret);
}


void Camera::eventCallback(unsigned nEvent, void *pCallBackCtx)
{
    Camera* pThis = static_cast<Camera*>(pCallBackCtx);
    if (TOUPCAM_EVENT_IMAGE == nEvent) {
        pThis->handleImageCallback();
    }
}

void Camera::handleImageCallback()
{
    HRESULT ret = 0;
    ret = Toupcam_PullImageV2(m_hToupcam, m_pData, 24, &m_imgInfo);
    if (SUCCEEDED(ret)) {
        m_image = Mat(m_imgInfo.height, m_imgInfo.width, CV_8UC3, m_pData, TDIBWIDTHBYTES(m_imgInfo.width * 24));
        cvtColor(m_image, m_image, COLOR_RGB2BGR);
        emit imageUpdated();
    }
}
