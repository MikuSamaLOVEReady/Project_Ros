# 声明要求的 cmake 最低版本
cmake_minimum_required(VERSION 2.8)

# 声明一个 cmake 工程
project(mapping)

# 设置编译模式
set(CMAKE_BUILD_TYPE "Debug")

# 寻找OpenCV库
find_package(OpenCV REQUIRED)
# 查找 Boost 库
find_package(Boost REQUIRED)
# 添加一个可执行程序
# 语法：add_executable( 程序名 源代码文件 ）

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include

)

add_library(${PROJECT_NAME} SHARED
src/system.cpp
src/uwb.cpp
src/mapping.cpp

)
add_executable(main src/main.cpp)


# 将库文件链接到可执行程序上
target_link_libraries(main ${OpenCV_LIBS} ${Boost_LIBRARIES} pthread)
target_link_libraries(main ${PROJECT_NAME})
