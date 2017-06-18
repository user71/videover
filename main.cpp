 #include <QCoreApplication>

#include "VideoReceiver.h"
#include "LogService.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    VideoReceiver vo = VideoReceiver();
    vo.initPath("/opt/SurvSys/");
    vo.updErrLog("/opt/SurvSys/errLog.log");
    vo.updFaceLog("/opt/SurvSys/faceLog.log");
    vo.updCameras("/opt/SurvSys/camera.conf");
    vo.updCamStatus();
    vo.up();
    vo.basicLoop();

    return a.exec();
}
