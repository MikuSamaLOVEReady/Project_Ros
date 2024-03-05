#include "../include/system.h"
#include "mapping.h"
#include "uwb.h"
#include "senddata.h"
#include "align.h"



namespace uwb_slam{
    System::System() {

        //threads init
        Uwb_ = std::make_shared<Uwb>();
        mp_Uwb = new std::thread(&Uwb::Run, Uwb_);

        Lighthouse_ = std::make_shared<Lighthouse>();
        mp_Lighthouse_ = new std::thread(&Lighthouse::Run, Lighthouse_);

        Align_ = std::make_shared<Align>(Uwb_,Lighthouse_);
        mp_Align = new std::thread(&Align::Run,Align_);

        Mapping_ = std::make_shared<Mapping>(Uwb_, Align_);
        mp_Mapping = new std::thread( &Mapping::Run, Mapping_);

        Sender_ = std::make_shared<Senddata>(Uwb_);
        mp_Senddata = new std::thread(&Senddata::Run , Sender_);


        Mapping_ = std::make_shared<Mapping>(Uwb_, Align_);
        mp_Mapping = new std::thread( &uwb_slam::Mapping::Run, Mapping_);

        Sender_ = std::make_shared<Senddata>(Uwb_);
        mp_Senddata = new std::thread(&Senddata::Run , Sender_);
    }

    
}