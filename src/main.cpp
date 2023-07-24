#include "../include/system.h"
#include "../include/uwb.h"
#include <iostream>

int main()
{
    uwb_slam::System* system = new uwb_slam::System();

    uwb_slam::Mapping* mp = new uwb_slam::Mapping();
    // system->Mapping_->Run();
    system->Run();
   
    
    //System->run()
}
