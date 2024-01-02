#include <cmath>
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <nav_msgs/Odometry.h>
#include "std_msgs/Float32MultiArray.h"
#include <utility>
#include <queue>
#include <fstream>
#include "ros_merge_test/RawImu.h"
#include "type.h"
#include "uwb.h"
#include "lighthouse.h"
#include "Mat.h"

#ifndef ALIGN_H
#define AlIGN_H
namespace uwb_slam{
    class Align
    {
    public:
        Align(){
            imuPos.Init(2, 1, 0);
            uwbPos.Init(2, 1, 0);
            syncPos.Init(2, 1, 0);
            imuStartPos.Init(2, 1, 0);
            Rotate.Init(2,2,0);
            uwbStartPos.Init(2,1,0);
            uwb_puber = nh_.advertise<std_msgs::Float32MultiArray>("uwb_data",10);

        };
        void Run();
        void wheel_odomCB(const nav_msgs::Odometry& wheel_odom);
        void imuCB(const ros_merge_test::RawImu& imu);
        void odomCB(const nav_msgs::Odometry& odom);

    public:
        ros::NodeHandle nh_;
        ros::Subscriber wheel_odom_sub_;
        ros::Subscriber imu_sub_;
        ros::Subscriber odom_sub_;
        Imu_odom_pose_data imu_odom_;
        Uwb_data uwb_data_;
        ros::Time imuDataRxTime, uwbDataRxTime, odomDataRxTime;
        Mat imuStartPos;
        Mat imuPos;
        Mat uwbPos;
        Mat syncPos;
        Mat Rotate;
        Mat uwbStartPos;
        ros::Time odom_tmp_ ;
        bool write_data_ = false;
        cv::Mat img1;
        std::queue<std::pair<Imu_odom_pose_data,Uwb_data>> data_queue;
        std::shared_ptr<uwb_slam::Uwb> uwb_;
        std::shared_ptr<uwb_slam::Lighthouse> lighthouse_;
        ros::Publisher uwb_puber;
    };
};
#endif
