#include "../include/system.h"
#include "../include/uwb.h"
#include "../include/lighthouse.h"
#include "Mat.h"


#include <iostream>
#include <ros/ros.h>
#include <thread>
#include "senddata.h"



int main(int argc, char** argv)
{
    ros::init(argc, argv, "locate_info_pub_node"); // Initialize the ROS node

    std::shared_ptr<uwb_slam::System> system = std::make_shared<uwb_slam::System>();

    ros::spin(); 
}
