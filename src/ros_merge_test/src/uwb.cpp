#include "uwb.h"
#include <cmath>

#define PI acos(-1)

namespace uwb_slam{

    //
    Uwb::Uwb(){
            //int pre_seq = -1;
            
           
        
    }

    void Uwb::Run() {
        ros::Rate loop_rate(10);
        wheel_odom_sub_=nh_.subscribe("wheel_odom",10,&Uwb::wheel_odomCB,this);
        imu_sub_=nh_.subscribe("raw_imu",10,&Uwb::imuCB,this);
        //  try{
        //     //s_port(io)// 替换成你的串口设备路径
        //     s_port.open("/dev/ttyUSB0"); 
        //     s_port.set_option(boost::asio::serial_port_base::baud_rate(115200)); // 设置波特率
        //     s_port.set_option(boost::asio::serial_port_base::character_size(8)); // 设置数据位
        //     s_port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        //     //size_t bytesRead = boost::asio::read(s_port, boost::asio::buffer(tmpdata, 13)); // 读取串口数据
    
        //  } catch (const std::exception& ex) {
        // std::cerr << "Exception: " << ex.what() << std::endl;
        // }

        while(1){
        this->Serread();
           // std::cout<<"s"<<std::endl;
           // std::cout<<this->x<<std::endl;
        /*if(t_tmp!=imu_odom_.imu_data_.imu_t_){
            imu_odom_queue_.push(imu_odom_);
            t_tmp=imu_odom_.imu_data_.imu_t_;
        }*/
        }


    }


    void Uwb::Serread(){
        
      

        
        try {
        boost::asio::io_service io;
        boost::asio::serial_port serial(io, "/dev/ttyUSB0"); // 替换成你的串口设备路径

        serial.set_option(boost::asio::serial_port_base::baud_rate(115200)); // 设置波特率
        serial.set_option(boost::asio::serial_port_base::character_size(8)); // 设置数据位
        serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none)); // 设置校验位
        serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one)); // 设置停止位

        uint8_t tmpdata[13];
        // std::cerr << "befor read" << std::endl;
        size_t bytesRead = boost::asio::read(serial, boost::asio::buffer(tmpdata, 13)); // 读取串口数据
        // std::cerr << "after read" << std::endl;

        // for (int i=0;i< bytesRead;i++)
        // {
        //     std::cout << "Received data: " << std::hex<<static_cast<int>(tmpdata[i]) ;
        // }
        memcpy(&this->distance, &tmpdata[4], sizeof(distance));
        memcpy(&this->theta, &tmpdata[8], sizeof(theta));
        /*this->x = cosf(theta/180*PI)*distance+1000;
        this->y = sinf(theta/180*PI)*distance+1000;
        this->theta = theta;*/
        this->uwb_data_.x_ = cosf(theta/180*PI)*distance+1000;
        this->uwb_data_.y_ = sinf(theta/180*PI)*distance+1000;
        this->uwb_data_.uwb_t_ = ros::Time::now(); 
        
        uwb_data_queue_.push(uwb_data_);
      
        //std::cout << "PI: " << PI << std::endl;
        cur_seq = static_cast<int>(tmpdata[3]);
        //std::cout << "****** cur _ sequence: " <<  cur_seq << "x: " << x << " y: " << y <<std::endl;
        if( cur_seq  - pre_seq != 1){
            std::cout << "****** cur _ sequence: " << cur_seq << "pre _ sequence: " << pre_seq << " ******\n";
        }
        pre_seq = static_cast<int>(tmpdata[3]);

        std::cout << "theta: " << theta << " distance: " << distance << std::endl;
        //std::cout std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }



    }
    void Uwb::wheel_odomCB(const nav_msgs::Odometry& wheel_odom)
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
    void Uwb::imuCB(const ros_merge_test::RawImu& imu)
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
    void Uwb::align()
    {

    }
    void fusion()
    {

    }

    


};

// bool Uwb::checknewdata()
// {
//     std::unique_lock<std::mutex> lock(mMutexUwb);
//     return !v_buffer_imu_odom_pose_data_.empty();
// }

// void Uwb::Run() {
//     while(1)
//     {
//         if(checknewdata())
//         {
//             {
//                 std::unique_lock<std::mutex> lock(mMutexUwb);
//                 Imu_odom_pose_data imu_odom_pose_data = v_buffer_imu_odom_pose_data_.front();
//                 v_buffer_imu_odom_pose_data_.pop();
//             }



//         }
//     }



// }

// void Uwb::feed_imu_odom_pose_data(const Imu_odom_pose_data& imu_odom_pose_data){
//     std::unique_lock<std::mutex> lock(mMutexUwb);
//     v_buffer_imu_odom_pose_data_.push(imu_odom_pose_data);
// }

