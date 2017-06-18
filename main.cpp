 #include <QCoreApplication>

#include "VideoReceiver.h"
#include "LogService.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    VideoReceiver vo = VideoReceiver();
    vo.updErrLog("/opt/SurvSys/errLog.log");
    vo.updFaceLog("/opt/SurvSys/faceLog.log");
    //vo.initSettings(std::vector<QString>());
    vo.updCameras("/opt/SurvSys/camera.conf");
    vo.updCamStatus();
    //LogService::getInstance().pushErrTextMessage("err");
    //LogService::getInstance().pushFaceDetectionMessage("face");
    //LogService::getInstance().pushErrTextMessage("err2");
    //LogService::getInstance().pushFaceDetectionMessage("face2");
    vo.up();
    vo.basicLoop();

    return a.exec();
}
