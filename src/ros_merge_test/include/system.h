#include <thread>
#include <string>
#include <iostream>

#ifndef SYSTEM_H
#define SYSTEM_H

namespace uwb_slam{

    class Mapping;
    class Senddata;
    class Uwb;
    class Align;
    class Lighthouse;

    class System{

    public:
        System();

    public:
       
        std::shared_ptr<uwb_slam::Mapping>Mapping_;
        std::shared_ptr<uwb_slam::Uwb>Uwb_;
        std::shared_ptr<uwb_slam::Senddata>Sender_;
        std::shared_ptr<uwb_slam::Align>Align_;
        std::shared_ptr<uwb_slam::Lighthouse>Lighthouse_;

        // Uwb* Uwb_ ;
        // Senddata* Sender_;
        // Mapping* Mapping_;
        std::thread* mp_Mapping;
        std::thread* mp_Uwb;
        std::thread* mp_Senddata;
        std::thread* mp_Align;
        std::thread* mp_Lighthouse_;

    };
}
#endif
