#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <tf2/LinearMath/Quaternion.h>
#include <mutex>
#include <memory>
#include "uwb.h"
#ifndef SENDDATA_H
#define SENDDATA_H


namespace uwb_slam{

    class Uwb;
    class Senddata
    {
        public:
        Senddata(){};
        explicit Senddata(std::shared_ptr<Uwb> uwb);
        void publishOdometry( std::shared_ptr<uwb_slam::Uwb>uwb);
        void Run();
        void odomCB(const nav_msgs::Odometry& odom);


        std::mutex mMutexSend;
        private:
        // subscriber
        ros::Publisher position_pub_;
        ros::Subscriber odom_sub_;
        ros::NodeHandle nh_;

        //publish
        nav_msgs::Odometry odom_;//odom的消息类型
        nav_msgs::Odometry sub_odom_;//odom的消息类型
        std::shared_ptr<Uwb> msp_Uwb;
      
    };

}

#endif