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
    void checkCams();
    Camera getCameraByIdx(int idx);
    //static void runCamera(Camera cam);
    void runCameras();

private:
    //static void captureCamera(Camera cam);
    void captureCamera(Camera cam);
    CameraVector m_cams;
};

#endif // CAMERAINTERACTOR_H
