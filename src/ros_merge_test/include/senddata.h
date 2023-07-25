#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <tf2/LinearMath/Quaternion.h>
#include <mutex>
#include "uwb.h"
#ifndef SENDDATA_H
#define SENDDATA_H


namespace uwb_slam{

    class Senddata
    {
        public:
        Senddata(){};
        void publishOdometry( Uwb* uwb);
        void Run(Uwb* uwb);


        std::mutex mMutexSend;
        private:
        ros::Publisher odom_pub_;
        ros::NodeHandle nh;
        nav_msgs::Odometry odom;//odom的消息类型

      
    };

}

#endif