#include <QCoreApplication>

#include "VideoReceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //VideoReceiver should be called here
    VideoReceiver vo = VideoReceiver();
    //set params here
    vo.updErrLog("errLog.log");
    vo.updFaceLog("faceLog.log");
    vo.initSettings(std::vector<QString>());
    vo.up();
    vo.basicLoop();

    return a.exec();
}
