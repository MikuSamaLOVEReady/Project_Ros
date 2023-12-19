#include <ros/ros.h>
#include <mutex>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <cstdint>
#include "type.h"
#include <queue>
#include <chrono>
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
        int pre_seq = -1;
        int cur_seq = -1;
        int AnchorNum = 3;
        int AnchorPos[3][3]={-240, 480, 0,\
                                240, 480, 0,\
                                240, -240, 0};//基站坐标，序号+三维坐标
        uint8_t tmpdata[13];
        uint16_t d[3];
     
    // std::queue<Imu_odom_pose_data> v_buffer_imu_odom_pose_data_;
   
       
        Uwb_data uwb_data_;
        // ros_merge_test::RawImu sub_imu_;
        // std::queue<Imu_odom_pose_data > imu_odom_queue_;
        // std::queue<Uwb_data> uwb_data_queue_;
        std::mutex mMutexUwb;
    //boost::asio::io_service io;
    //boost::asio::serial_port s_port;

    // Imu_odom_pose_data imu_odom_pose_data_;
    };

};






#endif
