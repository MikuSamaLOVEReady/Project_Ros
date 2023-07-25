#include "../include/system.h"
//#include ""


namespace uwb_slam{

    
    void System::Run()
    {
        
        // ros->imu->odom
       

    //    std::thread(&,run,);
        Uwb_->Serread();
        Mapping_->feed_uwb_data(Uwb_);
        Senddata_->publishOdometry(Uwb_);
    }
    
}