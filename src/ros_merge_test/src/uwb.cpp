#include "uwb.h"
#include <cmath>

#define PI acos(-1)

namespace uwb_slam{

    Uwb::Uwb() {

    }

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

    void Uwb::Serread(){
        try {
        boost::asio::io_service io;
        boost::asio::serial_port serial(io, "/dev/ttyUSB0"); // 替换成你的串口设备路径

        serial.set_option(boost::asio::serial_port_base::baud_rate(115200)); // 设置波特率
        serial.set_option(boost::asio::serial_port_base::character_size(8)); // 设置数据位
        serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none)); // 设置校验位
        serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one)); // 设置停止位

        uint8_t tmpdata[12];
        std::cerr << "befor read" << std::endl;
        size_t bytesRead = boost::asio::read(serial, boost::asio::buffer(tmpdata, 12)); // 读取串口数据
        std::cerr << "after read" << std::endl;

        for (int i=0;i< bytesRead;i++)
        {
            std::cout << "Received data: " << std::hex<<static_cast<int>(tmpdata[i]) << std::endl;
        }
        memcpy(&this->distance, &tmpdata[3], sizeof(distance));
        memcpy(&this->theta, &tmpdata[7], sizeof(theta));
        this->x = cosf(theta/180*PI)*distance;
        this->y = sinf(theta/180*PI)*distance;
        this->theta = theta;
        std::cout << "PI: " << PI << std::endl;
        std::cout << "theta: " << theta << " distance: " << distance << std::endl;
        std::cout << "x: " << x << " y: " << y << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    }

    void fusion()
    {

    }

    


};

