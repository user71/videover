#include "CameraInteractor.h"
#include "FlowAnalyzer.h"
#include <QProcess>
#include "opencv2/opencv.hpp"
#include <thread>
#include "LogService.h"
#include "common.h"
#include <QDateTime>

CameraInteractor::CameraInteractor()
{
  m_cams.clear();
}

CameraVector CameraInteractor::getCamsArray() const
{
  return m_cams;
}

void CameraInteractor::addCamera(Camera cam)
{
  m_cams.push_back(cam);
}

VO::Status CameraInteractor::checkCams()
{
  bool isAnyActive = false;

#ifdef PING_MODE
  #if defined(WIN32)
     QString parameter = "-n 1 -w 1";
  #else
     QString parameter = "-c 1 -w 1";
  #endif

  std::vector<Camera>::iterator pIt = m_cams.begin();
  for(; pIt != m_cams.end(); ++pIt)
  {
    int exitCode = QProcess::execute("ping", QStringList() << (*pIt).getIp() << parameter);
    if (exitCode == 0)
    {
        (*pIt).setActive(true);
        isAnyActive = true;
    } else
    {
        (*pIt).setActive(false);
        LogService::getInstance().pushErrTextMessage((*pIt).getIp());
    }
  }
#else
  std::vector<Camera>::iterator pIt = m_cams.begin();
  for(; pIt != m_cams.end(); ++pIt)
  {
    VideoCapture cap;
    int code;
    if (isCVEnum((*pIt).getIp().toStdString(), code) == VO::Status::eOk)
      cap = VideoCapture(code);
    else
      cap = VideoCapture((*pIt).getIp().toStdString());

    if(cap.isOpened())
    {
      (*pIt).setActive(true);
      isAnyActive = true;
    }
  }
#endif

  if (isAnyActive)
    return VO::eOk;
  else
    return VO::eNoActiveCameras;
}



Camera CameraInteractor::getCameraByIdx(int idx) const
{
  return m_cams.at(idx);
}

VO::Status CameraInteractor::runCameras()
{
  if (m_cams.size() == 0)
    return VO::Status::eNoCameras;

  std::vector<std::thread> threadsVar;
  std::vector<Camera>::iterator pIt = m_cams.begin();
  for (; pIt != m_cams.end(); ++pIt)
  {
    if ((*pIt).isActive())
    {
      threadsVar.push_back(std::thread(&CameraInteractor::captureCamera, this, (*pIt)));
    }
  }

  for (auto& th: threadsVar) th.join();

  return VO::Status::eOk;
}

void CameraInteractor::setPath(QString path)
{
  m_path = path;
}

void CameraInteractor::captureCamera(Camera cam)
{
  VideoCapture cap;
  int code;
  if (isCVEnum(cam.getIp().toStdString(), code) == VO::Status::eOk)
    cap = VideoCapture(code);
  else
    cap = VideoCapture(cam.getIp().toStdString());

  if (cap.isOpened())
  {
    QString dateTime = QDateTime::currentDateTime().toString();
    QString path = m_path;
    path = path + dateTime + ".avi";
    VideoWriter vWrt (path.toStdString(), CV_FOURCC('X', 'V', 'I', 'D'), 20, cv::Size(640, 480), true);

    while (true)
    {
      cv::Mat frame;
      cap >> frame;
      cv::resize(frame, frame, cv::Size(640, 480));
      bool isDetected = FlowAnalyzer::detectFace(frame, cam.getIp().toStdString());
      if (isDetected)
        LogService::getInstance().pushFaceDetectionMessage("Face Detected!", cam.getIp());
      vWrt.write(frame);
    }
  }else
  {
    LogService::getInstance().pushErrTextMessage("cv::VideoCapture is not opened. Camera addr: " + cam.getIp());
  }
}

VO::Status CameraInteractor::isCVEnum(const string &str, int &cvCode)
{
  if (str == "CV_CAP_ANY")
   {
     cvCode = CV_CAP_ANY;
     return VO::Status::eOk;
   }

  return VO::Status::eNotCVCode;
}
