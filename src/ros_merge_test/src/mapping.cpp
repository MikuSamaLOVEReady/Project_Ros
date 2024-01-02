#include "mapping.h"
#include <mutex>
#include <unistd.h>// 包含 usleep() 函数所在的头文件
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace uwb_slam
{
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

        int imuPosPointX = posData[0].x / PIXEL_SCALE + ( fmod(posData[0].x ,PIXEL_SCALE) != 0) + realWidth / 2;
        int imuPosPointY = posData[0].y / PIXEL_SCALE + ( fmod(posData[0].y ,PIXEL_SCALE) != 0) + realHeight / 2;
        int uwbPosPointX = posData[1].x / PIXEL_SCALE + ( fmod(posData[1].x ,PIXEL_SCALE) != 0) + realWidth / 2;
        int uwbPosPointY = posData[1].y / PIXEL_SCALE + ( fmod(posData[1].y ,PIXEL_SCALE) != 0) + realHeight / 2;
        int syncPosPointX = posData[2].x / PIXEL_SCALE + ( fmod(posData[2].x ,PIXEL_SCALE) != 0) + realWidth / 2;
        int syncPosPointY = posData[2].y / PIXEL_SCALE + ( fmod(posData[2].y ,PIXEL_SCALE) != 0) + realHeight / 2;
        // std::cout << "syncPos:" <<posData[2].x << " " << posData[2].y;
        // std::cout << " uwbPos:" <<posData[1].x << " " << posData[1].x;
        // std::cout << " imuPos:" <<posData[0].x << " " << posData[0].y << std::endl;

        // std::cout << "syncPos:" <<syncPosPointX << " " << syncPosPointY;
        // std::cout << " uwbPos:" <<uwbPosPointX << " " << uwbPosPointY;
        // std::cout << " imuPos:" <<imuPosPointX << " " << imuPosPointY << std::endl;
        // img.at<unsigned char>(imuPosPointY, imuPosPointX) = 0;   
        img.at<cv::Vec3b>(imuPosPointY, imuPosPointX) = cv::Vec3b(255,0,0);     //imu trace is red
        // img.at<cv::Vec3b>(uwbPosPointY, uwbPosPointX) = cv::Vec3b(0,255,0);     //uwb trace is green
        // img.at<cv::Vec3b>(syncPosPointY, syncPosPointX) = cv::Vec3b(255,0,0);   //sync trace is blue
    }


    void Mapping::Run()
    {
        
        //int key = cv::waitKey(0);//等待用户按下按键
        //std::cout << key << std::endl;
        realWidth = AREA_SIZE / PIXEL_SCALE;
        realHeight = AREA_SIZE / PIXEL_SCALE;

        img = cv::Mat(realHeight, realWidth, CV_8UC3, cv::Scalar(255,255,255));
        //cankao
        for (int j=0;j<AREA_SIZE / PIXEL_SCALE;j+=10)
            for (int i=0;i<AREA_SIZE / PIXEL_SCALE;i+=10)
                img.at<cv::Vec3b>(j,i)= cv::Vec3b(0,0,0);
        
        for (int j=realHeight/2-1; j<=realHeight/2+1; j+=1)
            for (int i=realWidth/2-1; i<=realWidth/2+1; i+=1)
                img.at<cv::Vec3b>(j,i)= cv::Vec3b(0,0,0);
        int i = 0, j = 0;
        img.at<cv::Vec3b>(j,i)= cv::Vec3b(0,0,0);



        cv::imshow("Image",img);

        // bool printFlag = 0;
        // std::ofstream outfile("data.txt",std::ofstream::out);
        // if(outfile.is_open()) {
        //     std::cout << "start saving data" << key << std::endl;
        //     printFlag = 1;
        // } else {
        //     std::cout<<"file can not open"<<std::endl;
        // }

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
                std::cout << "start mapping" << key << std::endl;
        
                //cv::destroyAllWindows();
            }
            while( readPos )//按下空格键
            {
                int key2 = cv::waitKey(1);
                if (key2 == 'q') {
                    //TODO: save

                    std::string pngimage="/home/firefly/Project_Ros11/Project_Ros1/src/ros_merge_test/Map/output_image.png";//保存的图片文件路径
                    cv::imwrite(pngimage,img);
                    readPos = false;
                    
                    // outfile.close();
                    // printFlag = 0;
                    // std::cout<< "Data written to file." << std::endl;
                    
                    break;
                }
        
                this->feedPos(cv::Point2d(align_->imuPos.mat[0][0], align_->imuPos.mat[1][0]), cv::Point2d(align_->uwbPos.mat[0][0], align_->uwbPos.mat[1][0]), cv::Point2d(align_->syncPos.mat[0][0], align_->syncPos.mat[1][0]));
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

