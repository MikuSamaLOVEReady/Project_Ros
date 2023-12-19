#include <thread>
#include <string>
#include <memory>

//#include "uwb.h"
//#include "senddata.h"
// #include "align.h"
//#include <iostream>

#ifndef SYSTEM_H
#define SYSTEM_H

namespace uwb_slam{

    class Mapping;
    class Senddata;
    class Uwb;

    class System{

    public:
        System();

    private:

        // RAII Obj
        std::shared_ptr<uwb_slam::Mapping>Mapping_;
        std::shared_ptr<uwb_slam::Uwb>Uwb_;
        std::shared_ptr<uwb_slam::Senddata>Sender_;

        //All Threads
        std::thread* mp_Mapping;
        std::thread* mp_Uwb;
        std::thread* mp_Senddata;
    };
}
#endif
