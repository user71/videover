#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class Camera
{
public:
    Camera();
    Camera(QString ip, bool activate);

    QString getIp() const;
    void setIp(QString str);
    bool isActive();
    void setActive(bool a);

private:
    QString m_Ip;
    bool m_Active;
};

typedef std::vector<Camera> CameraVector;


#endif // CAMERA_H
