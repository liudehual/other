project(STPusher)
include_directories(.)
include_directories(../BaseOS)
include_directories(/usr/local/libavformat)
include_directories(/usr/local/libavcodec)
include_directories(/usr/local/libavutil)
include_directories(/usr/local/libavfilter)
include_directories(/usr/local/libavdevice)
include_directories(/usr/local/libswscale)
include_directories(/usr/local/libswresample)

set(AudioPusher_SRC_LIST
	main.cpp
	STPusherLogSession.cpp
	STPusherLog.cpp
	STPusherObject.cpp
	STPusher.cpp
	STPusherAPI.cpp
	STPusherServerSession.cpp
	STPusherRTPSession.cpp
	STPusherServerSessionTimeoutTask.cpp
	STPusherRTPSessionTimeoutTask.cpp
	STPusherFramesManager.cpp
	STPusherH264Rtp.cpp
	STPusherRtp.cpp
	STPusherUtil.cpp
	STPusherAACRtp.cpp
	STPusherGetNetInterfaceInfo.cpp
)
link_directories("/usr/local/lib/")


add_executable(STPusher ${AudioPusher_SRC_LIST})
target_link_libraries(STPusher BaseOS pthread avutil avformat avcodec  avfilter avdevice swscale swresample SDL)
