#include "align.h"

namespace uwb_slam{
    void Align::Run()
    {
        imuDataRxTime = ros::Time::now();
        uwbDataRxTime = ros::Time::now();
        ros::Time::now();

        wheel_odom_sub_= nh_.subscribe("wheel_odom",10,&Align::wheel_odomCB,this);
        imu_sub_= nh_.subscribe("raw_imu",10,&Align::imuCB,this);
        odom_sub_= nh_.subscribe("odom",10,&Align::odomCB,this);

        std::ofstream outfile("data.txt",std::ofstream::out);
        if(outfile.is_open())
        {
            std::cout << "!!!" << std::endl;
            img1 = cv::Mat(200, 200, CV_8UC1, cv::Scalar(255,255,255));
            cv::imshow("Image1",img1);
            //int key2 = cv::waitKey(0);
            Mat prevPos(2, 1, 0);
            Mat detPos(2, 1, 0);
            Mat predPos(2, 1, 0);

            Mat R(2, 2, 1);
            Mat Q(2, 2 ,1);
            Q = Q * 0.001;
            Mat P(2, 2, 0);
            Mat F(2, 2, 1);
            Mat Kg(2, 2, 0);
            Mat Z(2, 2, 0);
            Mat H = F;
            Mat I = F;
            while(1){
                int key3 = cv::waitKey(1);
                if(key3 == 's'){
                    this->printFlag = 1;
                } else if (key3 == 'e') {
                    this->printFlag = 0;
                }
                if(imuDataRxTime!=imu_odom_.imu_data_.imu_t_){
                    imuPos.mat[0][0] = imu_odom_.pose_[0] * 100;
                    imuPos.mat[1][0] = imu_odom_.pose_[1] * 100;
                    detPos = imuPos - prevPos;
                    prevPos = imuPos;
                    if (uwbDataRxTime != uwb_->uwb_data_.uwb_t_) {
                        std::cout << "uwb received" << std::endl;
                        uwbPos.mat[0][0] = uwb_->uwb_data_.x_;
                        uwbPos.mat[1][0] = uwb_->uwb_data_.y_;
                        predPos = F * syncPos + detPos;
                        Z = H * uwbPos;
                        P = F * P * (~F) + Q;
                        Kg = P * (~H) / (H * P * (~H) + R);
                        syncPos = predPos + Kg * (Z - H * predPos);
                        P = (I - Kg * H) * P;
                        uwbDataRxTime = uwb_->uwb_data_.uwb_t_;
                    } else {
                        syncPos = syncPos + detPos;
                    }
                    imuDataRxTime = imu_odom_.imu_data_.imu_t_;
                    odomDataRxTime = odom_tmp_;

                    std::cout << "syncPos:" <<syncPos.mat[0][0] << " " << syncPos.mat[1][0];
                    std::cout << " uwbPos:" <<uwbPos.mat[0][0] << " " << uwbPos.mat[1][0];
                    std::cout << " imuPos:" <<imuPos.mat[0][0] << " " << imuPos.mat[1][0] << std::endl;
                    if (printFlag) {
                        outfile << std::left << std::setw(12)<<"imu_odom_: "<< std::setw(10)<< imu_odom_.imu_data_.imu_t_.sec << '.' <<std::setw(11)<< imu_odom_.imu_data_.imu_t_.nsec   << std::setw(11)
                        <<imu_odom_.imu_data_.a_[0]  << std::setw(11)<<imu_odom_.imu_data_.a_[1]  << std::setw(11)<<imu_odom_.imu_data_.a_[2]  << std::setw(12)
                        <<imu_odom_.imu_data_.w_[0]  << std::setw(12)<<imu_odom_.imu_data_.w_[1]  << std::setw(12)<<imu_odom_.imu_data_.w_[2]  << std::setw(11)
                        <<imu_odom_.vxy_  << std::setw(11)<<imu_odom_.angle_v_  << std::setw(7)
                        <<"   pose: "  << std::setw(1)<<(odom_tmp_-odomDataRxTime).sec<<'.'<<std::setw(12)<<(odom_tmp_-odomDataRxTime).nsec<<std::setw(11)
                        <<imu_odom_.pose_[0]  << std::setw(12)<<imu_odom_.pose_[1]  << std::setw(2)<<imu_odom_.pose_[2]  << std::setw(12)
                        <<imu_odom_.quat_[0]  << std::setw(12)<<imu_odom_.quat_[1]  << std::setw(12)<<imu_odom_.quat_[2]  << std::setw(12)<<imu_odom_.quat_[3]  << std::setw(6)
                        <<"   uwb: "  << std::setw(1)<<(uwb_->uwb_data_.uwb_t_-uwbDataRxTime).sec<<'.'<<std::setw(13)<<(uwb_->uwb_data_.uwb_t_-uwbDataRxTime).nsec   << std::setw(9)
                        <<uwb_->uwb_data_.x_  << std::setw(9)<<uwb_->uwb_data_.y_<<"\n";
                    }
                }
                
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
        // imu_odom_.pose_[0] = wheel_odom.pose.pose.position.x;
        // imu_odom_.pose_[1] = wheel_odom.pose.pose.position.y;
        // imu_odom_.pose_[2] = wheel_odom.pose.pose.position.z;
        // imu_odom_.quat_[0] = wheel_odom.pose.pose.orientation.x;
        // imu_odom_.quat_[1] = wheel_odom.pose.pose.orientation.y;
        // imu_odom_.quat_[2] = wheel_odom.pose.pose.orientation.z;
        // imu_odom_.quat_[3] = wheel_odom.pose.pose.orientation.w;

    
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

    void Align::odomCB(const nav_msgs::Odometry& odom)
    {
        odom_tmp_ = odom.header.stamp;
        imu_odom_.pose_[0] = odom.pose.pose.position.x;
        imu_odom_.pose_[1] = odom.pose.pose.position.y;
        imu_odom_.pose_[2] = odom.pose.pose.position.z;
        imu_odom_.quat_[0] = odom.pose.pose.orientation.x;
        imu_odom_.quat_[1] = odom.pose.pose.orientation.y;
        imu_odom_.quat_[2] = odom.pose.pose.orientation.z;
        imu_odom_.quat_[3] = odom.pose.pose.orientation.w;
    }











};



