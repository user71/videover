#include "Camera.h"

Camera::Camera()
{
    this->m_Ip = "";
    this->m_Active = false;
}

Camera::Camera(QString ip, bool activate)
{
  this->m_Ip = ip;
  this->m_Active = activate;
}

QString Camera::getIp() const
{
  return this->m_Ip;
}

void Camera::setIp(QString str)
{
    this->m_Ip = str;
}

bool Camera::isActive()
{
  return this->m_Active;
}

void Camera::setActive(bool a)
{
  this->m_Active = a;
}
