#include "../include/system.h"
#include "../include/uwb.h"
#include "senddata.h"



int main(int argc, char** argv)
{
    ros::init(argc, argv, "locate_info_pub_node"); // Initialize the ROS node
    ros::NodeHandle nh;

    std::cout << "woc" << std::endl;
    uwb_slam::System* system = new uwb_slam::System();

    uwb_slam::Mapping* mp = new uwb_slam::Mapping();

    system->Uwb_ = new uwb_slam::Uwb();
    // system->Mapping_->Run();
    system->Run();

    ros::spin(); // Start the ROS node's main loop
    //System->run()
}
