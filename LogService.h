#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "common.h"
#include <mutex>

class LogService
{
    public:
        static LogService& getInstance()
        {
            static LogService instance;
            return instance;
        }

        void initErrTextLog(QString logFilePath);
        void initFaceTextLog(QString logFilePath);
        void pushErrTextMessage(QString message) const;
        void pushFaceDetectionMessage(QString message, QString camAddr = "") const;
        bool isFaceLogActive() const;
        bool isErrLogActive() const;

    private:
        LogService() {}
        LogService(LogService const&);
        void operator= (LogService const&);

        QString m_textLogFilePath;
        QString m_facesTextLogFilePath;
        mutable std::mutex m_errLogMutex;
        mutable std::mutex m_faceLogMutex;
};

#endif // LOGSERVICE_H
