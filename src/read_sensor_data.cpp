#include <read_sensor_data.h>


void set_uwb(Uwb * uwb)
{
    uwb_ = uwb;
}


void imu_call_back(const ImuConstPtr& imu){
    Imu_data d1= Imu_data(imu.linear_acceleration.x,imu.linear_acceleration.y,imu.linear_acceleration.z,imu.angular_velocity.x,imu.angular_velocity.y,imu.angular_velocity.z);
    
}
void odom_call_back(const OdomConstPtr& odom){
  Odom_data d1 = Odom_data(odom.pose.pose.position,odom.pose.pose.orientation,odom.header.stamp,odom.twist.linear.x,odom.twist.linear.y,odom.angular.z);

}
void Run(int argc, char* argv[]){

    ros::init(argc, argv, "imu_odom");
    // 创建一个节点句柄
    ros::NodeHandle nh;
    imu_sub_ = nh.subscribe("imu/data_raw", 1000,imu_call_back);
    odom_sub_ =nh.subscribe("odom", 1000,odom_call_back);
    ros::spin();
}