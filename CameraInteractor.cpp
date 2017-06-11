#include "CameraInteractor.h"
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

  /*
  if(cam.isActive())
  {
    std::thread camThread(&CameraInteractor::captureCamera, cam);
    camThread.join();
  }else
  {
      //error-code or something should be returned
  }*/
}

//void CameraInteractor::captureCamera(Camera cam)
void CameraInteractor::captureCamera(Camera cam)
{
/*
#include <iostream>
#include <thread>
#include "opencv2/opencv.hpp"
#include <vector>
using namespace std;
using namespace cv;
void detect(Mat img, String strCamera) {
  string cascadeName1 = "haar_cascade_for_people_detection.xml";
  CascadeClassifier detectorBody;
  bool loaded1 = detectorBody.load(cascadeName1);
  Mat original;
  img.copyTo(original);
  vector human;
  cvtColor(img, img, CV_BGR2GRAY);
  equalizeHist(img, img);
  detectorBody.detectMultiScale(img, human, 1.1, 2, 0 | 1, Size(40, 80), Size(400,480 ));
  if (human.size() > 0)
    {
      for (int gg = 0; gg < human.size(); gg++)
      {
      rectangle(original, human[gg].tl(), human[gg].br(), Scalar(0, 0, 255), 2, 8, 0);
      }
    }
  imshow("Detect " + strCamera, original);
  int key6 = waitKey(40);
//End of the detect
}
void stream(String strCamera) {
VideoCapture cap(strCamera);
 if (cap.isOpened()) {
      while (true) {
        Mat frame;
        cap >> frame;
        resize(frame, frame, Size(640, 480));
        detect(frame, strCamera);
     }
   }
}
int main() {
    thread cam1(stream, "http://xxxxxxxR");
    thread cam2(stream, "http://xxxxxxxR");
    cam1.join();
    cam2.join();
    return 0;
}
 */
}
