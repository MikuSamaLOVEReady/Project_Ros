#ifndef SYSTEM_H
#define SYSTEM_H

#include <thread>
#include <string>

class Mapping;



class System{

public:
    System() : Mapping_(nullptr){}

private:
    Mapping* Mapping_;


};
#endif
