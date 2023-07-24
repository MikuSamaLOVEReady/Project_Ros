#ifndef SYSTEM_H
#define SYSTEM_H

#include <thread>
#include <string>
#include "mapping.h"
#include "uwb.h"
#include <iostream>

namespace uwb_slam{
    class System{

    public:
        System() {
            Mapping_ = new Mapping();
        }
        void Run(){
    
            Uwb_->Serread( *Uwb_);
            std::cout<<Uwb_->x<<std::endl;
        };
    public:
        Mapping* Mapping_;
        Uwb* Uwb_;

    };
}
#endif
