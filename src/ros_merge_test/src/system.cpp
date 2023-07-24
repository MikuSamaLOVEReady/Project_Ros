#include "../include/system.h"
//#include ""


namespace uwb_slam{

    
    void System::Run()
    {
        
        // ros->imu->odom
       

    //    std::thread(&,run,);
        Uwb_->Serread();
        std::cout<<"s"<<std::endl;
        std::cout<<Uwb_->x<<std::endl;
    }
    
}