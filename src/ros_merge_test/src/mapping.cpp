#include "mapping.h"
#include <mutex>
#include <unistd.h>// 包含 usleep() 函数所在的头文件
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace uwb_slam
{
    Mapping::Mapping(std::shared_ptr<uwb_slam::Uwb> uwb):
    uwb_(uwb)
    {

    }

    bool Mapping::checkQueue()
    {
        //std::unique_lock<std::mutex> lock(mMutexMap);
        return !posDataQueue.empty();
    }

    void Mapping::feedPos(const cv::Point2d & imuPosData, const cv::Point2d & uwbPosData, const cv::Point2d & syncPosData)
    {
        //std::unique_lock<std::mutex> lock(mMutexMap);
        posDataQueue.push({imuPosData, uwbPosData, syncPosData});

    }
    

    void Mapping::process()
    {
        {
            //std::unique_lock<std::mutex> lock(mMutexMap);
            //std::cout << "SIZE:  " <<posDataQueue.size() << std::endl;
            posData = posDataQueue.front();
            //std::cout << "x: " <<cur_point.x << " y:" << cur_point.y << std::endl;
            posDataQueue.pop();
        }
        /*生成图*/

        int imuPosPointX = posData[0].x / PIXEL_SCALE + ( fmod(posData[0].x ,PIXEL_SCALE) != 0);
        int imuPosPointY = posData[0].y / PIXEL_SCALE + ( fmod(posData[0].y ,PIXEL_SCALE) != 0);
        int uwbPosPointX = posData[1].x / PIXEL_SCALE + ( fmod(posData[1].x ,PIXEL_SCALE) != 0);
        int uwbPosPointY = posData[1].y / PIXEL_SCALE + ( fmod(posData[1].y ,PIXEL_SCALE) != 0);
        int syncPosPointX = posData[2].x / PIXEL_SCALE + ( fmod(posData[2].x ,PIXEL_SCALE) != 0);
        int syncPosPointY = posData[2].y / PIXEL_SCALE + ( fmod(posData[2].y ,PIXEL_SCALE) != 0);

        // img.at<unsigned char>(imuPosPointY, imuPosPointX) = 0;   
        img.at<cv::Vec3b>(imuPosPointY, imuPosPointX) = cv::Vec3b(0,0,255);
        img.at<cv::Vec3b>(uwbPosPointY, uwbPosPointX) = cv::Vec3b(0,255,0);
        img.at<cv::Vec3b>(syncPosPointY, syncPosPointX) = cv::Vec3b(255,0,0);

        //cv::imshow("Image",img);
    }


    void Mapping::Run()
    {
        
        //int key = cv::waitKey(0);//等待用户按下按键
        //std::cout << key << std::endl;
        int realWidth = AREA_SIZE / PIXEL_SCALE;
        int realHeight = AREA_SIZE / PIXEL_SCALE;

        img = cv::Mat(realHeight, realWidth, CV_8UC3, cv::Scalar(255,255,255));
        //cankao
        for (int j=0;j<AREA_SIZE / PIXEL_SCALE;j+=16)
            for (int i=0;i<AREA_SIZE / PIXEL_SCALE;i+=16)
                img.at<cv::Vec3b>(j,i)= cv::Vec3b(0,0,255);
        
        for (int j=199+8;j<210;j+=1)
            for (int i=199+8;i<210;i+=1)
                img.at<cv::Vec3b>(j,i)= cv::Vec3b(0,0,255);



        cv::imshow("Image",img);

        /*
        std::cout << "waiting" <<std::endl;
        int key = cv::waitKey(0);
        if (key == 'q' || key == 27) {
            this->feed_uwb_data(cv::Point2d(uwb_->x,uwb_->y));
            readPos = true;
            std::cout << "non" << key << std::endl;
            cv::destroyAllWindows();
         }
        */
        while(1){
            int key = cv::waitKey(0);
            if (key == 'q' ) {
                readPos = true;
                std::cout << "non" << key << std::endl;
                //cv::destroyAllWindows();
            }
            while( readPos )//按下空格键
            {
                int key2 = cv::waitKey(1);
                if (key2 == 'q' ) {
                    //TODO: save
                //   std::cout << << std::endl;
                  std::string pngimage="/home/firefly/Project_Ros/src/ros_merge_test/Map/output_image.png";//保存的图片文件路径
        	      cv::imwrite(pngimage,img);
                  readPos = false;
                  break;
                }
        
                this->feedPos(cv::Point2d(align_->imuPos.mat[0][0], align_->imuPos.mat[1][0]),
                              cv::Point2d(align_->uwbPos.mat[0][0], align_->uwbPos.mat[1][0]),
                              cv::Point2d(align_->syncPos.mat[0][0], align_->syncPos.mat[1][0]));
                //this->feedPos(cv::Point2d(uwb_->x, uwb_->y));

                //uwb xieru
                //std::cout << "cur_SEQ: " <<uwb_->cur_seq  << std::endl;

                if(checkQueue())
                {
                    //std::cout << " start process" << std::endl;
                    process();
                    //std::cout << " end process" << std::endl;
                     
                }
            }
            // std::cout << "out" << key << std::endl;

        }



        //std::string pngimage="../Map/pngimage.png";//保存的图片文件路径
        //cv::imwrite(pngimage,img);
      
        /*ros 发送图片给导航 */
    }


} // namespace uwb_slam

