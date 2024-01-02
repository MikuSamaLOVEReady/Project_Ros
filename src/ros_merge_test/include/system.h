#include <thread>
#include <string>
#include "mapping.h"
#include "uwb.h"
#include "senddata.h"
// #include "align.h"
#include <iostream>

#ifndef SYSTEM_H
#define SYSTEM_H

namespace uwb_slam{
    class System{

    public:
        System() {
        }
        void Run();
    public:
       
        std::shared_ptr<uwb_slam::Mapping>Mapping_;
        std::shared_ptr<uwb_slam::Uwb>Uwb_;
        std::shared_ptr<uwb_slam::Senddata>Sender_;
        std::shared_ptr<uwb_slam::Align>Align_;
        std::shared_ptr<uwb_slam::Lighthouse>Lighthouse_;

        // Uwb* Uwb_ ;
        // Senddata* Sender_;
        // Mapping* Mapping_;
    };
}
#endif
