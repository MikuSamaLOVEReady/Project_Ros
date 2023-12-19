#include <queue>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "uwb.h"
#include "align.h"

#ifndef MAPPING_H
#define MAPPING_H


namespace uwb_slam{
    class Mapping
    {
        public:
        const double PIXEL_SCALE = 5.0;     //xiangsudian cm
        const int    AREA_SIZE = 1000;      //map size cm
        Mapping() = default;
        explicit Mapping(std::shared_ptr<uwb_slam::Uwb> uwb);
        void Run();
        bool checkQueue();
        void feedPos(const cv::Point2d & imuPosData, const cv::Point2d & uwbPosData, const cv::Point2d & syncPosData);
        void process();
        std::mutex mMutexMap;
        std::shared_ptr<uwb_slam::Uwb> uwb_;
        std::shared_ptr<uwb_slam::Align> align_;

        private:
        std::queue<std::vector<cv::Point2d>> posDataQueue;
        std::vector<cv::Point2d> posData = std::vector<cv::Point2d>(3, {-1, -1});
        //cv::Point2d imuPoint = {-1,-1};
        // std::queue<cv::Point2d> posDataQueue;
        

        bool readPos = false;
        cv::Mat img;
    };

}

#endif
