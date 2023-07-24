#include <mutex>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <cstdint>
// #include "type.h"
#include <queue>
#ifndef UWB_H
#define UWB_H


namespace uwb_slam{

    class Uwb
    {
    public:
        Uwb();
        void Run();
        bool checknewdata();
        void feed_imu_odom_pose_data();
        void Serread();

 
   public:
    
    float x, y, theta, distance;
    // std::queue<Imu_odom_pose_data> v_buffer_imu_odom_pose_data_;

    std::mutex mMutexUwb;

    // Imu_odom_pose_data imu_odom_pose_data_;
    };

};






#endif
