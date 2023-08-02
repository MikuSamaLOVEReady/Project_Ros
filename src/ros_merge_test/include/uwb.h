#include <ros/ros.h>
#include <mutex>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <cstdint>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include "ros_merge_test/RawImu.h"
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
        void wheel_odomCB(const nav_msgs::Odometry& wheel_odom);
        void imuCB(const ros_merge_test::RawImu& imu);
        void align();

 
    public:
        int pre_seq = -1;
        int cur_seq = -1;
        uint8_t tmpdata[13];
        float x, y, theta, distance;
     
    // std::queue<Imu_odom_pose_data> v_buffer_imu_odom_pose_data_;
        ros::NodeHandle nh_;
        ros::Subscriber wheel_odom_sub_;
        ros::Subscriber imu_sub_;
      
        Imu_odom_pose_data imu_odom_;
        Uwb_data uwb_data_;
        // ros_merge_test::RawImu sub_imu_;
        std::queue<Imu_odom_pose_data > imu_odom_queue_;
        std::queue<Uwb_data> uwb_data_queue_;
        std::mutex mMutexUwb;
    //boost::asio::io_service io;
    //boost::asio::serial_port s_port;

    // Imu_odom_pose_data imu_odom_pose_data_;
    };

};






#endif
