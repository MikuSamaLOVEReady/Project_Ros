#include "lighthouse.h"
#include <cmath>
#include <string>

namespace uwb_slam{
    Lighthouse::Lighthouse(){
        std::cout << "Start Run. "  << std::endl;

        // 创建UDP套接字
        UdpSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (UdpSocket == -1) {
            std::cerr << "Error creating UDP socket." << std::endl;
            return;
        }

        std::cout << "Creating UDP socket sucess. "  << std::endl;

        // 设置套接字地址结构
        sockaddr_in udpAddress;
        std::memset(&udpAddress, 0, sizeof(udpAddress));
        udpAddress.sin_family = AF_INET;
        udpAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        udpAddress.sin_port = htons(PORT);

        // 将套接字绑定到地址
        if (bind(UdpSocket, (struct sockaddr*)&udpAddress, sizeof(udpAddress)) == -1) {
            std::cerr << "Error binding UDP socket." << std::endl;
            close(UdpSocket);
        }
    }

    Lighthouse::~Lighthouse(){
        close(UdpSocket);
    }

    void Lighthouse::Run() {
        while(1){
            // 这是一个阻塞线程
            this->UDPRead();
        }
    }

    void Lighthouse::UDPRead(){
        char buffer[1024];
        ssize_t bytesRead = recvfrom(UdpSocket, buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (bytesRead == -1) {
            std::cerr << "Error receiving data." << std::endl;
            return;
        }

        std::string data(buffer);

        float x,y,z,qw,qx,qy,qz;

        qw = 1.0;

        sscanf(data.c_str(),"%f %f %f %f %f %f",&x,&y,&z,&qx,&qy,&qz);

        mMutexLighthouse.lock();

        this->data.x_ = x;
        this->data.y_ = y;
        this->data.z_ = z;

        this->data.qw_ = qw;
        this->data.qx_ = qx;
        this->data.qy_ = qy;
        this->data.qz_ = qz;

        

        mMutexLighthouse.unlock();

        // 打印接收到的消息
        buffer[bytesRead] = '\0';
        //std::cout << "Received: " << buffer << std::endl;

    }
};