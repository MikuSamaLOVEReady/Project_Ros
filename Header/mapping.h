#include <vector>
#include <opencv2/opencv.hpp>
#include <mutex>

#ifndef MAPPING_H
#define MAPPING_H


namespace uwb_slam{
class Mapping
{
    public:
    const double PIXEL_SCALE = 5.0;
    Mapping() = default;
    void Run();
    bool check_uwb_point();
    void feed_uwb_data(const cv::Point2d & data);
    void process();


    std::mutex mMutexMap;



    private:
    std::vector<cv::Point2d> mv_uwb_point_;

};

}

#endif