#include "CameraInteractor.h"
#include "FlowAnalyzer.h"
#include <QProcess>
#include "opencv2/opencv.hpp"
#include <thread>
#include "LogService.h"
#include "common.h"

CameraInteractor::CameraInteractor()
{
    m_cams.clear();
}

CameraVector CameraInteractor::getCamsArray()
{
  return m_cams;
}

void CameraInteractor::addCamera(Camera cam)
{
    m_cams.push_back(cam);
}

VO::Status CameraInteractor::checkCams()
{
  #if defined(WIN32)
     QString parameter = "-n 1 -w 1";
  #else
     QString parameter = "-c 1 -w 1";
  #endif

  bool isAnyActive = false;
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

  if (isAnyActive)
    return VO::eOk;
  else
    return VO::eNoActiveCameras;
}

Camera CameraInteractor::getCameraByIdx(int idx)
{
  return m_cams.at(idx);
}

void CameraInteractor::runCameras()
{
  CameraVector activeCameras;
  std::vector<Camera>::iterator pIt = m_cams.begin();
  for (; pIt != m_cams.end(); ++pIt)
  {
    if ((*pIt).isActive())
      activeCameras.push_back(*pIt);
  }

  std::vector<std::thread> threadsVar;
  std::vector<Camera>::iterator pIt2 = activeCameras.begin();
  for (; pIt2 != activeCameras.end(); ++pIt2)
  {
    threadsVar.push_back(std::thread(&CameraInteractor::captureCamera, this, (*pIt)));
  }

  for (auto& th: threadsVar) th.join();

}

void CameraInteractor::captureCamera(Camera cam)
{
  cv::VideoCapture cap(cam.getIp().toStdString());
  if (cap.isOpened()) {
    while (true) {
    cv::Mat frame;
    cap >> frame;
    cv::resize(frame, frame, cv::Size(640, 480));
    bool isDetected = FlowAnalyzer::detectFace(frame, cam.getIp().toStdString());
    if (isDetected)
      LogService::getInstance().pushFaceDetectionMessage("Face Detected!", cam.getIp());
    }

  }else{
    LogService::getInstance().pushErrTextMessage("cv::VideoCapture is not opened. Camera addr: " + cam.getIp());
  }

}
