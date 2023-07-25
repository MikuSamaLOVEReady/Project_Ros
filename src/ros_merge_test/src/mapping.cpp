#include "mapping.h"
#include <mutex>
#include <unistd.h>// 包含 usleep() 函数所在的头文件
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace uwb_slam
{
    bool Mapping::check_uwb_point()
    {
        std::unique_lock<std::mutex> lock(mMutexMap);
        return !mv_uwb_point_.empty();
    }

    void Mapping::feed_uwb_data(const cv::Point2d & data)
    {
            std::unique_lock<std::mutex> lock(mMutexMap);
            mv_uwb_point_.push(data);
    }
    

    void Mapping::process()
    {
        {
            std::unique_lock<std::mutex> lock(mMutexMap);
            cur_point= mv_uwb_point_.front();
            mv_uwb_point_.pop();
        }
        /*生成图*/

        int pix_x = cur_point.x / PIXEL_SCALE + ( fmod(cur_point.x ,PIXEL_SCALE) != 0);
        int pix_y = cur_point.y / PIXEL_SCALE + ( fmod(cur_point.y ,PIXEL_SCALE) != 0);

        img.at<unsigned char>(pix_y,pix_x)= 0;
        cv::imshow("Image",img);
    }


    void Mapping::Run()
    {
        
        //int key = cv::waitKey(0);//等待用户按下按键
        //std::cout << key << std::endl;
        int realWidth = AREA_SIZE / PIXEL_SCALE;
        int realHeight = AREA_SIZE / PIXEL_SCALE;

        img = cv::Mat(realHeight, realWidth, CV_8UC1, cv::Scalar(255,255,255));
        cv::imshow("Image",img);

        /*
        std::cout << "waiting" <<std::endl;
        int key = cv::waitKey(0);
        if (key == 'q' || key == 27) {
            this->feed_uwb_data(cv::Point2d(uwb_->x,uwb_->y));
            read_uwb_ = true;
            std::cout << "non" << key << std::endl;
            cv::destroyAllWindows();
         }
        */
        while(1){
            int key = cv::waitKey(0);
            if (key == 'q' ) {
                read_uwb_ = true;
                //std::cout << "non" << key << std::endl;
                //cv::destroyAllWindows();
            }
            //std::cout << "non" << key << std::endl;
            while( read_uwb_ )//按下空格键
            {
                int key2 = cv::waitKey(1);
                if (key2 == 'q' ) {
                    //TODO: save
                  read_uwb_ = false;
                  break;
                }

                this->feed_uwb_data(cv::Point2d(abs(uwb_->x) * 100,abs(uwb_->y)*100));
                //uwb xieru
                std::cout << "anxia " << std::endl;

                if(check_uwb_point())
                {
                    process();
                }
            }
            std::cout << "out" << key << std::endl;

        }



        //std::string pngimage="../Map/pngimage.png";//保存的图片文件路径
        //cv::imwrite(pngimage,img);
      
        /*ros 发送图片给导航 */
    }
} // namespace uwb_slam

