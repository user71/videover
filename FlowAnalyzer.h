#ifndef FLOWANALYZER_H
#define FLOWANALYZER_H

#include "opencv2/opencv.hpp"

using namespace cv;

class FlowAnalyzer
{
public:
    FlowAnalyzer();
    static bool detectFace(Mat img, String strCamera);
};

#endif // FLOWANALYZER_H
