#include "LogService.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

void LogService::initErrTextLog(QString logFilePath)
{
  this->m_textLogFilePath = logFilePath;
}

void LogService::initFaceTextLog(QString logFilePath)
{
  this->m_facesTextLogFilePath = logFilePath;
}

void LogService::pushIpTextMessage(QString message)
{
  if (this->isErrLogActive())
  {
    QFile file(this->m_textLogFilePath);
    if (file.open(QIODevice::ReadWrite)) {
      QTextStream stream(&file);
      QString dateTime = QDateTime::currentDateTime().toString();
      stream << "[" << dateTime << "] : " << message << endl;
    }
    file.close();
  }
}

void LogService::pushFaceDetectionMessage(QString message, QString camAddr)
{
  if (this->isFaceLogActive())
  {
    QFile file(this->m_textLogFilePath);
    if (file.open(QIODevice::ReadWrite)) {
      QTextStream stream(&file);
      QString dateTime = QDateTime::currentDateTime().toString();
      stream << "[" << dateTime << "] : " << message << " ; Camera address: "<< camAddr << endl;
    }
    file.close();
  }
}

bool LogService::isFaceLogActive()
{
  return !this->m_facesTextLogFilePath.isEmpty();
}

bool LogService::isErrLogActive()
{
  return !this->m_textLogFilePath.isEmpty();
}
