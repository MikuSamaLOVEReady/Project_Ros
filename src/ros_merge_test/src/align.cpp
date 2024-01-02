#include "align.h"

namespace uwb_slam{
    void Align::Run()
    {
        imuDataRxTime = ros::Time::now();
        uwbDataRxTime = ros::Time::now();

        wheel_odom_sub_= nh_.subscribe("wheel_odom",10,&Align::wheel_odomCB,this);
        imu_sub_= nh_.subscribe("raw_imu",10,&Align::imuCB,this);
        odom_sub_= nh_.subscribe("odom",10,&Align::odomCB,this);

        std::ofstream outfile("data.txt",std::ofstream::out);
        if(outfile.is_open()) {
            std::cout << "start saving data" << std::endl;
            outfile << "imuDataRxTime,odomDataRxTime,uwbDataRxTime,"\
                    << "aX,aY,aZ,"\
                    << "wX,wY,wZ,"\
                    << "qX,qY,qZ,qW,"\
                    << "vXY,angleV,"\
                    << "imuPosX,imuPosY,"\
                    << "uwbPosX,uwbPosY,"\
                    << "syncPosX,syncPosY,"\
                    << "lightHousePosX,lightHousePosY,lightHousePosZ,"
                    << "d1,d2,d3\n";
        } else {
            std::cout<<"file can not open"<<std::endl;
        }
        
        Mat prevPos(2, 1, 0);
        Mat detPos(2, 1, 0);
        Mat predPos(2, 1, 0);
        Mat R(2, 2, 1);
        Mat Q(2, 2 ,1);
        Q = Q * 0.00001;
        Mat P(2, 2, 0);
        Mat F(2, 2, 1);
        Mat Kg(2, 2, 0);
        Mat Z(2, 2, 0);

        uwbStartPos.mat[0][0]=9;
        uwbStartPos.mat[1][0]=0;
        Mat H = F;
        Mat I = F;
        bool imuStartFlag = 1;
        bool printFlag = 0;
        double qx, qy, qz, qw;
        float roll, imuStartRoll;
        while(1){
            // int key3 = cv::waitKey(1);
            // if(key3 == 's'){
            //     printFlag = 1;
            // } else if (key3 == 'e') {
            //     printFlag = 0;
            // }
            if(imuDataRxTime!=imu_odom_.imu_data_.imu_t_){
                std::cout << "imu received" << std::endl;
                imuPos.mat[0][0] = imu_odom_.pose_[0] * 100;
                imuPos.mat[1][0] = imu_odom_.pose_[1] * 100;
                qx = imu_odom_.quat_[0];
                qy = imu_odom_.quat_[1];
                qz = imu_odom_.quat_[2];
                qw = imu_odom_.quat_[3];
                roll = -atan2(2*(qw*qz+qx*qy),1-2*(qy*qy+qz*qz));

                std::cout<<"roll:"<<roll<<std::endl;
                if (imuStartFlag == 1 && imuPos.mat[0][0] != 0 && imuPos.mat[1][0] != 0) {
                    imuStartRoll = roll-PI/2;
                    imuStartPos = imuPos;
                    imuStartFlag = 0;
                }
                //std::cout << imuStartPos.mat[0][0] << " " << imuStartPos.mat[1][0] << std::endl;
                roll = roll - imuStartRoll;
                imuPos = imuPos - imuStartPos;
                detPos = imuPos - prevPos;
                prevPos = imuPos;
                if (uwbDataRxTime != uwb_->uwb_data_.uwb_t_) {
                    std::cout << "uwb received" << std::endl;

                    Rotate.mat[0][0] = cos(roll);
                    Rotate.mat[0][1] = -sin(roll);
                    Rotate.mat[1][0] = sin(roll);
                    Rotate.mat[1][1] = cos(roll);

                    uwbPos.mat[0][0] = uwb_->uwb_data_.x_;
                    uwbPos.mat[1][0] = uwb_->uwb_data_.y_;

                    uwbPos = uwbPos - Rotate * uwbStartPos;

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

                std::cout << "syncPos:" << syncPos.mat[0][0] << " " << syncPos.mat[1][0];
                std::cout << " uwbPos:" << uwbPos.mat[0][0] << " " << uwbPos.mat[1][0];
                std::cout << " imuPos:" << imuPos.mat[0][0] << " " << imuPos.mat[1][0];
                // std::cout << " lightHousePos:" << lighthouse_->data.x_ << " " << lighthouse_->data.y_ ;
                std::cout << std::endl;

                
                outfile << imuDataRxTime << "," << odomDataRxTime << "," << uwbDataRxTime <<","\
                        << imu_odom_.imu_data_.a_[0] << "," << imu_odom_.imu_data_.a_[1] << "," << imu_odom_.imu_data_.a_[2] << ","\
                        << imu_odom_.imu_data_.w_[0] << "," << imu_odom_.imu_data_.w_[1] << "," << imu_odom_.imu_data_.w_[2] << ","\
                        << qx << "," << qy << "," << qz << "," << qw << ","\
                        << imu_odom_.vxy_ << "," <<imu_odom_.angle_v_ << ","\
                        << imuPos.mat[0][0] << "," << imuPos.mat[1][0] << ","\
                        << uwbPos.mat[0][0] << "," << uwbPos.mat[1][0] << ","\
                        << syncPos.mat[0][0] << "," << syncPos.mat[1][0] << ","\
                        << lighthouse_->data.x_ << "," << lighthouse_->data.y_ << "," << lighthouse_->data.z_ << ","\
                        << uwb_->d[0] << "," << uwb_->d[1] << "," << uwb_->d[2] << "\n";
            }
            
        }

        // outfile.close();
        // std::cout<< "Data written to file." << std::endl;   
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



