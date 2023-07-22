#include <vector>
#include <cmath>

#ifndef ALIGN_H
#define AlIGN_H
namespace uwb_slam{
    class Align
    {
    public:
        Align() = default;
        bool check_uwb_point(const int undef) {};
        void alignUwbAndImudata();

    };
};
#endif
