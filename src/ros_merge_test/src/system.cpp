#include "../include/system.h"
//#include ""


namespace uwb_slam{

    void System::Run()
    {
        while(1){
            Uwb_->Serread();
            std::cout<<"s"<<std::endl;
            std::cout<<Uwb_->x<<std::endl;
        }


    }
    
}