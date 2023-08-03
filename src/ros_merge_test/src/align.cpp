#include "align.h"

namespace uwb_slam{
    void Align::Run()
    {
        tmp = ros::Time::now();
        ros::Time tmp1 = ros::Time::now();
        // ros::Rate loop_rate(10);
        wheel_odom_sub_= nh_.subscribe("wheel_odom",10,&Align::wheel_odomCB,this);
        imu_sub_= nh_.subscribe("raw_imu",10,&Align::imuCB,this);
        std::ofstream outfile("data.txt",std::ofstream::out);
        if(outfile.is_open()){
        int count = 0;
        outfile <<"imu_odom_: "<< "imu_timestamp"<<"imu_linear_acc_x_y_z"<<"imu_angular_x_y_z"<<
                "odom_vxy"<<"odom_angle_v_"<<"\n";
        while(1){
            
            if(tmp!=imu_odom_.imu_data_.imu_t_){
                count++;
                outfile <<"imu_odom_: "<< "imu_timestamp  "<<"imu_linear_acc_x_y_z  "<<"imu_angular_x_y_z  "<<
                "odom_vxy  "<<"odom_angle_v_  "<<"\n";

                if(tmp1!=uwb_->uwb_data_.uwb_t_){
                     outfile <<"imu_odom_: "<< imu_odom_.imu_data_.imu_t_ <<"*"<<imu_odom_.imu_data_.a_[0]<<"*"<<
                     imu_odom_.imu_data_.a_[1]<<"*"<<imu_odom_.imu_data_.a_[2]<<"*"<<imu_odom_.imu_data_.w_[0]<<"*"<<imu_odom_.imu_data_.w_[1]<<"*"<<imu_odom_.imu_data_.w_[2]<<"*"<<imu_odom_.vxy_<<"*"<<
                    imu_odom_.angle_v_<<
                    "uwb: "<<uwb_->uwb_data_.uwb_t_<<"*"<<uwb_->uwb_data_.x_<<"*"<<uwb_->uwb_data_.y_<<"\n";
                     tmp1 = uwb_->uwb_data_.uwb_t_;
                 }
               else{
                outfile <<"imu_odom_: "<< imu_odom_.imu_data_.imu_t_ <<"*"<<imu_odom_.imu_data_.a_[0]<<"*"<<
                    imu_odom_.imu_data_.a_[1]<<"*"<<imu_odom_.imu_data_.a_[2]<<"*"<<imu_odom_.imu_data_.w_[0]<<"*"<<imu_odom_.imu_data_.w_[1]<<"*"<<imu_odom_.imu_data_.w_[2]<<"*"<<imu_odom_.vxy_<<"*"<<
                    imu_odom_.pose_[0]<<"*"<<imu_odom_.pose_[0]<<"*"<<imu_odom_.pose_[0]<<
                    "uwb: "<<uwb_->uwb_data_.uwb_t_<<"\n";
                    std::cout << "uwb_data_: " << uwb_data_.uwb_t_<< std::endl;
                    //tmp = imu_odom_.imu_data_.imu_t_;
               }
                tmp = imu_odom_.imu_data_.imu_t_;
                    
                // tmp1 = uwb_->uwb_data_.uwb_t_;
                
                
            }
            if(count>300)
                break;
        }

        outfile.close();
        std::cout<< "Data written to file." << std::endl;
        }
        else{
            std::cout<<"file can not open"<<std::endl;
        }
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



