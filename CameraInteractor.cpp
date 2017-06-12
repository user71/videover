#include "CameraInteractor.h"
#include "FlowAnalyzer.h"
#include <QProcess>
#include "opencv2/opencv.hpp"
#include <thread>
#include "LogService.h"

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

void CameraInteractor::checkCams()
{
  #if defined(WIN32)
     QString parameter = "-n 1 -w 1";
  #else
     QString parameter = "-c 1 -w 1";
  #endif

  QVector<Camera>::iterator pIt = m_cams.begin();
  for(; pIt != m_cams.end(); ++pIt)
  {
    int exitCode = QProcess::execute("ping", QStringList() << (*pIt).getIp() << parameter);
    if (exitCode == 0)
    {
        (*pIt).setActive(true);
    } else
    {
        (*pIt).setActive(false);
        LogService::getInstance().pushIpTextMessage((*pIt).getIp());
    }
  }
}

Camera CameraInteractor::getCameraByIdx(int idx)
{
  return m_cams.at(idx);
}

// runCamera and captureCamera SHOULD BE IN VideoReceiver ???

/*void CameraInteractor::runCamera(Camera cam)
{
  if(cam.isActive())
  {
    std::thread camThread(&CameraInteractor::captureCamera, cam);
    camThread.join();
  }else
  {
      //error-code or something should be returned
  }
}*/

void CameraInteractor::runCameras()
{
  CameraVector activeCameras;
  QVector<Camera>::iterator pIt = m_cams.begin();
  for (; pIt != m_cams.end(); ++pIt)
  {
    if ((*pIt).isActive())
      activeCameras.push_back(*pIt);
  }

  //QVector<std::thread> threadsVar;
  std::vector<std::thread> threadsVar;
  QVector<Camera>::iterator pIt2 = activeCameras.begin();
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
         FlowAnalyzer::detectFace(frame, cam.getIp().toStdString());
      }
  }
}
