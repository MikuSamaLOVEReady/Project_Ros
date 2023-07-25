#ifndef SYSTEM_H
#define SYSTEM_H

#include <thread>
#include <string>
#include "mapping.h"
#include "uwb.h"
#include "senddata.h"
#include <iostream>

namespace uwb_slam{
    class System{

    public:
        System() {
        }
        void Run();
    public:
        Mapping* Mapping_;
        Uwb* Uwb_ ;
        Senddata* Sender_;
    };
}
#endif
