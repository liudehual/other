PROJECT(BaseOS)
cmake_minimum_required(VERSION 2.8)
include_directories(.)
SET(BaseOS_SRC  atomic.cpp
			   EventContext.cpp
			   InternalStdLib.cpp
			   IdleTask.cpp
			   MyAssert.cpp
			   OS.cpp
			   OSCond.cpp
			   OSFileSource.cpp
			   OSHeap.cpp
			   OSRef.cpp
			   OSMutex.cpp
			   OSMutexRW.cpp
			   OSQueue.cpp
			   OSThread.cpp
			   QueryParamList.cpp
			   ResizeableStringFormatter.cpp
			   SDPUtils.cpp
			   Socket.cpp
			   SocketUtils.cpp
			   StringFormatter.cpp
			   StringParser.cpp
			   StringTranslator.cpp
			   StrPtrLen.cpp
			   Task.cpp
			   TCPListenerSocket.cpp
			   TCPSocket.cpp
			   TimeoutTask.cpp
			   UDPDemuxer.cpp
			   UDPSocket.cpp
			   UDPSocketPool.cpp
			   UserAgentParser.cpp
			   StreamLinkRef.cpp
				)
if(LINUX)
	SET(BaseOS_SRC ${BaseOS_SRC} ev.cpp ev_hw.cpp HWFile.cpp ev_epoll.cpp)
elseif(HI3520D)
	SET(BaseOS_SRC ${BaseOS_SRC} ev.cpp ev_hw.cpp HWFile.cpp ev_epoll.cpp)
else()
	SET(BaseOS_SRC ${BaseOS_SRC} win32ev.cpp)
endif()

ADD_LIBRARY(BaseOS STATIC ${BaseOS_SRC})
