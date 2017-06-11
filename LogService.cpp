#include "LogService.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

void LogService::initTextLog(QString logFilePath)
{
  this->m_textLogFilePath = logFilePath;
}

void LogService::pushIpTextMessage(QString message)
{
  QFile file(this->m_textLogFilePath);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream stream(&file);
    QString dateTime = QDateTime::currentDateTime().toString();
    stream << "[" << dateTime << "] : " << message << endl;
  }
  file.close();
}

void LogService::pushFaceDetectionMessage(QString message, QString camAddr)
{
  QFile file(this->m_textLogFilePath);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream stream(&file);
    QString dateTime = QDateTime::currentDateTime().toString();
    stream << "[" << dateTime << "] : " << message << " ; Camera address: "<< camAddr << endl;
  }
  file.close();
}
