#include "senddata.h"
#include "uwb.h"

namespace uwb_slam
{
    Senddata::Senddata(std::shared_ptr<Uwb> uwb)
    : nh_() , odom_() , sub_odom_() , msp_Uwb(uwb)
    {
        position_pub_=nh_.advertise<nav_msgs::Odometry>("uwb_odom",50);
        odom_sub_=nh_.subscribe("odom",10,&Senddata::odomCB,this);
    }

    void Senddata::Run(){
        ros::Rate loop_rate(10);
        while(ros::ok()){
            publishOdometry(msp_Uwb);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }
    void Senddata::odomCB(const nav_msgs::Odometry& odom){
        sub_odom_ = odom;
        return;
    }

    void Senddata::publishOdometry(std::shared_ptr<uwb_slam::Uwb>uwb)
    {

        std::mutex mMutexSend;
        ros::Time current_time = ros::Time::now();

        // 设置 Odometry 消息的头部信息
        odom_.header.stamp = current_time;
        odom_.header.frame_id = "odom";  // 设置坐标系为 "map"
        odom_.child_frame_id = "base_link";  // 设置坐标系为 "base_link"
        
        // 填充 Odometry 消息的位置信息
        odom_.pose.pose.position.x = uwb->uwb_data_.x_;
        odom_.pose.pose.position.y = uwb->uwb_data_.y_;
        odom_.pose.pose.position.z = 0.0;
        

        // 填充 Odometry 消息的姿态信息（使用四元数来表示姿态）
        // tf2::Quaternion quat;
        // quat.setRPY(0, 0, uwb->theta);  // 设置了 yaw 角度，其他 roll 和 pitch 设置为 0
        // odom.pose.pose.orientation.x = quat.x();
        // odom.pose.pose.orientation.y = quat.y();
        // odom.pose.pose.orientation.z = quat.z();
        // odom.pose.pose.orientation.w = quat.w();

        odom_.pose.pose.orientation.x = sub_odom_.pose.pose.orientation.x;
        odom_.pose.pose.orientation.y = sub_odom_.pose.pose.orientation.y;
        odom_.pose.pose.orientation.z = sub_odom_.pose.pose.orientation.z;
        odom_.pose.pose.orientation.w = sub_odom_.pose.pose.orientation.w;

        // 发布 Odometry 消息
        position_pub_.publish(odom_);


    }




} // namespace uwb_slam