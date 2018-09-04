#include <stdio.h>
#include <stdlib.h>
#include "Server.h"
#include <pthread.h>
#include "StartServer.h"
#include "Daemon.h"
void usage()
{
	fprintf(stderr,"-v       : print usage\n");
	fprintf(stderr,"-h       : print usage\n");
	fprintf(stderr,"-p XXX   : Bind to special port \n");
	fprintf(stderr,"-d       : Run Background \n");
}
int main(int argc,char *argv[])
{
	UInt16 thePort=0;
	int ch;
	bool doFork=false;
    while ((ch = getopt(argc,argv, "vdp:h")) != EOF){
        switch(ch){
            case 'v':
                usage();
                ::exit(0);
            case 'p':
            	thePort=::atoi(optarg);
                break;
            case 'd':
            	doFork=true;
            	break;
            case 'h':
                usage();
                ::exit(0);
            default:
                break;
        }
    }
    if(doFork){
		if (daemon(0,0) != 0){
            exit(-1);
        }
    }
	
	StartServer(thePort);
	RunServer();
	return 1;
}
