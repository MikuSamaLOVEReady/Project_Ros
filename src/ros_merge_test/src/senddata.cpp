#include "senddata.h"


namespace uwb_slam
{
    void Senddata::Run(Uwb* uwb){

        ros::Rate loop_rate(10);
        odom_pub_=nh.advertise<nav_msgs::Odometry>("odom",50);
        while(ros::ok()){
            std::cout<< "rui" <<std::endl;
            publishOdometry(uwb);
            ros::spinOnce();
            loop_rate.sleep();
        }


    }

    void Senddata::publishOdometry(uwb_slam::Uwb *uwb)
    {
        std::cout << "LLL" << std::endl;

        std::mutex mMutexSend;
        ros::Time current_time = ros::Time::now();

        // 设置 Odometry 消息的头部信息
        odom.header.stamp = current_time;
        odom.header.frame_id = "map";  // 设置坐标系为 "map"
        odom.child_frame_id = "base_link";  // 设置坐标系为 "base_link"

        // 填充 Odometry 消息的位置信息
        odom.pose.pose.position.x = uwb->x;
        odom.pose.pose.position.y = uwb->y;
        odom.pose.pose.position.z = 0.0;


        // 填充 Odometry 消息的姿态信息（使用四元数来表示姿态）
        tf2::Quaternion quat;
        quat.setRPY(0, 0, uwb->theta);  // 设置了 yaw 角度，其他 roll 和 pitch 设置为 0
        odom.pose.pose.orientation.x = quat.x();
        odom.pose.pose.orientation.y = quat.y();
        odom.pose.pose.orientation.z = quat.z();
        odom.pose.pose.orientation.w = quat.w();

        // 发布 Odometry 消息
        odom_pub_.publish(odom);


    }


    


} // namespace uwb_slam