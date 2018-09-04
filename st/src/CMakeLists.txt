PROJECT(ST)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall -g -fPIC)

#编译推流器
#add_subdirectory(Pusher)

#编译基础库
add_subdirectory(BaseOS)

#编译服务器
add_subdirectory(STServer)

#编译音频推流器
add_subdirectory(STPusher)
