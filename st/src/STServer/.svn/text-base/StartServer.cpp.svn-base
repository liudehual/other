#include "StartServer.h"
#include "Server.h"
#include "Log.h"
#include "OS.h"

static Server *sServer=NULL;

int StartServer(unsigned int inPortOverride)
{
	OS::Initialize();
	sServer=new Server;
	sServer->initialize(inPortOverride);
	sServer->startServer();
}
int RunServer()
{
	fprintf(stderr,"Start Server Succeed \n");
	while(1){
		OSThread::Sleep(1000*1000);
	}
}