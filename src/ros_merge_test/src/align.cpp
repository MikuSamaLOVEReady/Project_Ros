#include "align.h"

namespace uwb_slam{
    void Align::Run()
    {
        ros::Rate loop_rate(10);
        wheel_odom_sub_= nh_.subscribe("wheel_odom",10,&Align::wheel_odomCB,this);
        imu_sub_= nh_.subscribe("raw_imu",10,&Align::imuCB,this);
    }
    
    void Align::wheel_odomCB(const nav_msgs::Odometry& wheel_odom)
    {
        imu_odom_.vxy_= wheel_odom.twist.twist.linear.x;
        imu_odom_.angle_v_ = wheel_odom.twist.twist.angular.z;
        imu_odom_.pose_[0] = wheel_odom.pose.pose.position.x;
        imu_odom_.pose_[1] = wheel_odom.pose.pose.position.y;
        imu_odom_.pose_[2] = wheel_odom.pose.pose.position.z;
        imu_odom_.quat_[0] = wheel_odom.pose.pose.orientation.x;
        imu_odom_.quat_[1] = wheel_odom.pose.pose.orientation.y;
        imu_odom_.quat_[2] = wheel_odom.pose.pose.orientation.z;
        imu_odom_.quat_[3] = wheel_odom.pose.pose.orientation.w;
    
        return;
    }
    void Align::imuCB(const ros_merge_test::RawImu& imu)
    {
        imu_odom_.imu_data_.imu_t_ = imu.header.stamp;
        imu_odom_.imu_data_.a_[0] = imu.raw_linear_acceleration.x;
        imu_odom_.imu_data_.a_[1] = imu.raw_linear_acceleration.y;
        imu_odom_.imu_data_.a_[2] = imu.raw_linear_acceleration.z;

        imu_odom_.imu_data_.w_[0] = imu.raw_angular_velocity.x;
        imu_odom_.imu_data_.w_[1] = imu.raw_angular_velocity.y;
        imu_odom_.imu_data_.w_[2] = imu.raw_angular_velocity.z;

        return;
    }










};



