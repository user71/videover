#ifndef CAMERAINTERACTOR_H
#define CAMERAINTERACTOR_H

#include "common.h"
#include "Camera.h"

class CameraInteractor
{
public:
    CameraInteractor();
    CameraVector getCamsArray();
    void addCamera(Camera cam);
    VO::Status checkCams();
    Camera getCameraByIdx(int idx);
    void runCameras();

private:
    void captureCamera(Camera cam);
    CameraVector m_cams;
};

#endif // CAMERAINTERACTOR_H
