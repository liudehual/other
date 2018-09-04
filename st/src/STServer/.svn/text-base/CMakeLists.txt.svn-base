PROJECT(STServer)
include_directories(.)
include_directories(../BaseOS)
set(STServer_SRC
	Server.cpp
	Object.cpp
	ConfigFileParser.cpp
	UserAuthentication.cpp
	CommonListener.cpp
	ClientSession.cpp
	RTPSession.cpp
	LogSession.cpp
	Log.cpp
	main.cpp
	StartServer.cpp
	GetOpt.cpp
	GetNetInterfaceInfo.cpp
	Util.cpp
	Daemon.cpp
	
)
add_executable(SaiTengServer ${STServer_SRC})
target_link_libraries(SaiTengServer BaseOS pthread)
