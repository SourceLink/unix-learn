#include "apue.h"
#include <fcntl.h>


int
main(int argc,char* argv[])
{
	int value;
	
	if(argc != 2)
	{
		err_quit("usage: a.out <decriptor#>");
	}

	if((value = fcntl(atoi(argv[1]),F_GETFL,0)) < 0)
	{
		err_sys("fcntl error for fd %d",atoi(argv[1]));
	}
	
	switch(value & O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only");
		break;
		
		case O_WRONLY:
			printf("write only");
		break;

		case O_RDWR:
			printf("read write");
		break;

		default:
			err_dump("unknow access mode");
		break;
	}	

	if(value & O_APPEND)
	{
		printf(",append");
	}
	if(value & O_NONBLOCK)
	{
		printf(",nonblocking");
	}	
	if(value & O_SYNC)
	{
		printf(",sysnchronous writes");
	}

	#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSNC != O_SYNC)
	if(value & O_FSYNC)
	{
		printf(",syschronous writes");
	}
	#endif

	putchar('\n');

	exit(0);
}
