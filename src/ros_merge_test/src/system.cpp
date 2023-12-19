#include "../include/system.h"
#include "mapping.h"
#include "uwb.h"
#include "senddata.h"


namespace uwb_slam{

    System::System() {

        //threads init
        Uwb_ = std::make_shared<Uwb>();
        mp_Uwb = new std::thread(&Uwb::Run, Uwb_);

        Mapping_ = std::make_shared<Mapping>(Uwb_);
        mp_Mapping = new std::thread( &uwb_slam::Mapping::Run, Mapping_);

        Sender_ = std::make_shared<Senddata>(Uwb_);
        mp_Senddata = new std::thread(&Senddata::Run , Sender_);
    }


}