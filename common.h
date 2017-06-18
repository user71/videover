#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <QString>
#include <QVector>
#include <memory>

namespace VO{
  enum Status
  {
    eOk = 0,
    eVideoCaptureIsNotOpened = 1,
    eCascadeIsNotLoaded = 2,
    eErrLogIsNotActive = 3,
    eFaceLogIsNotActive = 4,
    eNoActiveCameras = 5,
    eCantOpenFileForRead = 6,
    eCantOpenFileForWrite = 7,
    eNotCVCode = 8,
  };
}

//typedef /*std::string*/QString String;

#endif // COMMON_H
