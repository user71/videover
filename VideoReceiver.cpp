#include "VideoReceiver.h"
#include "CameraInteractor.h"
#include "LogService.h"

VideoReceiver::VideoReceiver()
{
  m_drop = false;
}

void VideoReceiver::drop()
{
  m_drop = true;
}

void VideoReceiver::up()
{
  m_drop = false;
}

void VideoReceiver::initSettings(std::vector<QString> addrs)
{
    this->m_addrs = addrs;
}

void VideoReceiver::updFaceLog(QString log)
{
  m_faceLog = log;
}

void VideoReceiver::updErrLog(QString log)
{
  m_ErrLog = log;
}

void VideoReceiver::basicLoop()
{
  while (!m_drop) {
    CameraInteractor interact;

    for (auto& a: m_addrs)
    {
      Camera c(a, false);
      interact.addCamera(c);
    }

    LogService::getInstance().initFaceTextLog(m_faceLog);
    LogService::getInstance().initErrTextLog(m_ErrLog);

    interact.checkCams();
    interact.runCameras();
  }
}
