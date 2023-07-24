#include <uwb.h>
#include <ros/ros.h>
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <boost/thread/mutex.hpp>
#include "type.h"


#ifndef READ_SENSOR_DATA_H
#define READ_SENSOR_DATA_H

namespace uwb_slam{


typedef boost::shared_ptr<nav_msgs::Odometry const> OdomConstPtr;
typedef boost::shared_ptr<sensor_msgs::Imu const> ImuConstPtr;
class Read_sensor_data
{
    public:
    Read_sensor_data();
   
    void Run();
  
    private:
    ros::Subscriber imu_sub_;
    ros::Subscriber odom_sub_;

    Uwb* uwb_;
}
}
#endif