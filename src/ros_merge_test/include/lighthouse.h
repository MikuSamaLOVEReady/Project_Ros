#include <ros/ros.h>
#include <mutex>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <cstdint>
#include "type.h"
#include <queue>
#include <chrono>
#ifndef __LIGHTHOUSE_H__
#define __LIGHTHOUSE_H__

namespace uwb_slam{
class Lighthouse{
public:
    Lighthouse();
    ~Lighthouse();
    void Run();
    void UDPRead();
    // Listen PORT
    int PORT = 12345;
    int UdpSocket = -1;

    LightHouseData data;

    std::mutex mMutexLighthouse;
};
};
#endif
