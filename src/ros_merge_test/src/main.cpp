#include "../include/system.h"
#include "../include/uwb.h"
#include <iostream>
#include <ros/ros.h>
#include <thread>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ros_merge_test_node"); // Initialize the ROS node
    ros::NodeHandle nh;

    std::cout << "woc" << std::endl;
    uwb_slam::System* system = new uwb_slam::System();
    uwb_slam::Mapping* mp = new uwb_slam::Mapping();

    system->Uwb_ = new uwb_slam::Uwb();
    mp->uwb_ = system->Uwb_;


    // system->Mapping_->Run();
    std::thread rose_trd ([&system]() {
        system->Run();
    });
    std::thread map_trd ([&mp]() {
        mp->Run();
    });



    //

    ros::spin(); // Start the ROS node's main loop
    //System->run()
}
