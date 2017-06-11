#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "common.h"

class LogService
{
    public:
        static LogService& getInstance()
        {
            static LogService instance;
            return instance;
        }

        QString m_textLogFilePath;
        QString m_facesTextLogFilePath;
        void initErrTextLog(QString logFilePath);
        void initFaceTextLog(QString logFilePath);
        void pushIpTextMessage(QString message);
        void pushFaceDetectionMessage(QString message, QString camAddr = "");
        bool isFaceLogActive();
        bool isErrLogActive();

    private:
        LogService() {}
        LogService(LogService const&);
        void operator= (LogService const&);
};

#endif // LOGSERVICE_H
