cmake_minimum_required(VERSION 3.24)
project(ROS)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/Header
        ${EIGEN3_INCLUDE_DIR}
        ${Pangolin_INCLUDE_DIRS}
        /usr/local/include
)

add_executable(ROS Header/uwb.h Header/system.h Header/mapping.h Header/avoid.h
        Header/align.h src/main.cpp src/system.cpp src/mapping.cpp src/align.cpp src/uwb.cpp)

target_link_libraries(ROS ${OpenCV_LIBS})