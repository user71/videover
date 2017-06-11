#ifndef VIDEORECEIVER_H
#define VIDEORECEIVER_H

#include "common.h"

class VideoReceiver
{
public:
    VideoReceiver();
    void basicLoop();
    void initSettings(QVector<QString> addrs);
    void updFaceLog(QString log);
    void updErrLog(QString log);
    void drop();
    void up();
private:
    QVector<QString> m_addrs;
    QString m_faceLog;
    QString m_ErrLog;
    bool m_drop;
};

#endif // VIDEORECEIVER_H
