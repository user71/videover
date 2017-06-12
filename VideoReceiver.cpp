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
  LogService::getInstance().initFaceTextLog(m_faceLog);
}

void VideoReceiver::updErrLog(QString log)
{
  m_ErrLog = log;
  LogService::getInstance().initErrTextLog(m_ErrLog);
}

void VideoReceiver::updCameras()
{
  for (auto& a: m_addrs)
  {
    Camera c(a, false);
    m_interactor.addCamera(c);
  }
}

void VideoReceiver::updCamStatus()
{
  m_camStatus = m_interactor.checkCams();
}

void VideoReceiver::basicLoop()
{
  while (!m_drop) {
    if (m_camStatus != VO::eNoActiveCameras)
      m_interactor.runCameras();
  }
}
