#include "uwb.h"
#include <cmath>
#include "Mat.h"

#define PI acos(-1)

namespace uwb_slam{
    Mat A;
    Mat b;
    Mat uwbPos;
    //
    Uwb::Uwb(){
        for(int i=0; i<3; i++)
        {

            for(int j=0; j<3; j++)
            {
                std::cout<<AnchorPos[i][j]<<" ";
            }
            std::cout<<std::endl;
            
        }
        A.Init(2,2,0);
        b.Init(2,1,0);
        uwbPos.Init(2,1,0);
        for(int i=0; i<2; i++)
        {
            A.mat[i][0] = -2*(this->AnchorPos[0][0]-this->AnchorPos[i+1][0]);
            A.mat[i][1] = -2*(this->AnchorPos[0][1]-this->AnchorPos[i+1][1]);
        
        }
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<2; j++)
            {
                std::cout<<A.mat[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    
    }

    void Uwb::Run() {
        
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

        uint8_t tmpdata[9];
        // std::cerr << "befor read" << std::endl;
        size_t bytesRead = boost::asio::read(serial, boost::asio::buffer(tmpdata, 9)); // 读取串口数据
        // std::cerr << "after read" << std::endl;
        this->uwb_data_.uwb_t_ = ros::Time::now();
        
        // for (int i=0;i< bytesRead;i++)
        // {
        //     std::cout << std::hex<<static_cast<int>(tmpdata[i]) << " ";
        // }
        // std::cout << std::endl;
        memcpy(&this->d[0], &tmpdata[3], sizeof(uint16_t));
        memcpy(&this->d[1], &tmpdata[5], sizeof(uint16_t));
        memcpy(&this->d[2], &tmpdata[7], sizeof(uint16_t));
        //std::cout << "d:" << d[0] << " " << d[1] << " " << d[2] << std::endl;
        if(abs(d[1] + d[2] + d[0]) >6000) {
            return;
        }
        for(int i=0; i<2; i++)
        {
            b.mat[i][0] = (this->d[0]*this->d[0]-this->d[i+1]*this->d[i+1])\
                        -(this->AnchorPos[0][0]*this->AnchorPos[0][0]-this->AnchorPos[i+1][0]*this->AnchorPos[i+1][0])\
                        -(this->AnchorPos[0][1]*this->AnchorPos[0][1]-this->AnchorPos[i+1][1]*this->AnchorPos[i+1][1]);
        }
        Mat AT=~A;
        uwbPos=(AT*A)%AT*b;
        this->uwb_data_.x_ = uwbPos.mat[0][0];
        this->uwb_data_.y_ = uwbPos.mat[1][0];
        //std::cout << "uwbPos:" << this->uwb_data_.x_ << " " << this->uwb_data_.y_ << std::endl;
         
        
        // uwb_data_queue_.push(uwb_data_);
      
        //std::cout << "uwb_data_: " << uwb_data_.uwb_t_<< std::endl;
        // cur_seq = static_cast<int>(tmpdata[3]);
        //std::cout << "****** cur _ sequence: " <<  cur_seq << "x: " << x << " y: " << y <<std::endl;
        // if( cur_seq  - pre_seq != 1){
        //     std::cout << "****** cur _ sequence: " << cur_seq << "pre _ sequence: " << pre_seq << " ******\n";
        // }
        // pre_seq = static_cast<int>(tmpdata[3]);

        // std::cout << "theta: " << theta << " distance: " << distance << std::endl;
        //std::cout std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }



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

