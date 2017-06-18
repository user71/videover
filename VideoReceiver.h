#ifndef VIDEORECEIVER_H
#define VIDEORECEIVER_H

#include "common.h"
#include "CameraInteractor.h"

class VideoReceiver
{
public:
    VideoReceiver();
    void basicLoop();
    void initSettings(std::vector<QString> addrs);
    void updFaceLog(QString log);
    void updErrLog(QString log);
    void drop();
    void up();
    VO::Status updCameras(QString pathToCr);
    void updCamStatus();
    void initPath(QString path);
private:
    std::vector<QString> m_addrs;
    QString m_faceLog;
    QString m_ErrLog;
    bool m_drop;
    CameraInteractor m_interactor;
    VO::Status m_camStatus;
};

#endif // VIDEORECEIVER_H
