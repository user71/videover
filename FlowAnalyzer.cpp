#include "FlowAnalyzer.h"

FlowAnalyzer::FlowAnalyzer()
{
}

bool FlowAnalyzer::detectFace(Mat img, String strCamera)
{
  string cascadeName1 = "/opt/SurvSys/haarcascade_frontalface_default.xml";
  CascadeClassifier detectorFace;
  bool isCascadeLoaded = detectorFace.load(cascadeName1);

  if (!isCascadeLoaded)
      return false;

  Mat original;
  img.copyTo(original);
  cvtColor(img, img, CV_BGR2GRAY);
  equalizeHist(img, img);

  std::vector<Rect> humanFace;
  detectorFace.detectMultiScale(img, humanFace, 1.1, 2, 0 | 1, Size(40, 80), Size(400,480 ));

  if (humanFace.size() > 0)
  {
    return true;
  }

  return false;
}
