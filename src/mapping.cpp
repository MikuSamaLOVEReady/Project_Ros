#include "mapping.h"
#include <mutex>
#include <unistd.h>// 包含 usleep() 函数所在的头文件
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace uwb_slam
{
    bool Mapping::check_uwb_point()
    {
        return !mv_uwb_point_.empty();
    }
    
    void Mapping::feed_uwb_data(const cv::Point2d & data)
    {
            std::unique_lock<std::mutex> lock(mMutexMap);
            mv_uwb_point_.push_back(data);
    }
    

    void Mapping::process()
    {
        {
            std::unique_lock<std::mutex> lock(mMutexMap);
            cv::Point2d a = mv_uwb_point_.front();
            mv_uwb_point_.pop_back();
        }
        /*生成图*/
        
        int realWidth = 900 / PIXEL_SCALE;  
        int realHeight = 900 / PIXEL_SCALE;  

        cv::Mat image(realHeight, realWidth, CV_8UC1, cv::Scalar(255,255,255));
    }


    void Mapping::Run()
    {
        int key = cv::waitKey(0);//等待用户按下按键
        if(key == 32)//按下空格键

        while(1)
        {
            if(check_uwb_point())
            {
                process();

            }
            if(key == 27)//按下esc键
                break;

            usleep(1000000);

        }


        std::string pngimage="./pngimage.png";//保存的图片文件路径
        //cv::imwrite(pngimage,image);
      
        /*ros 发送图片给导航 */
    }
} // namespace uwb_slam

