#include "apue.h"
#include <fcntl.h>



void set_fl(int fd,int flag);




int
main(void)
{
	int fd;

	if((fd = open("source.txt",O_RDONLY | O_CREAT,06666)) < 0)
	{
		err_sys("open error");
	}

	set_fl(fd,O_NONBLOCK);  /* set source.txt's flag no block */

	close(fd);  	     /* close source.txt */

	exit(0);
}




/*
 *flags are file staus flags to turn on 
 * */
void set_fl(int fd, int flag)
{
	int value;

	/* get file flag */
	if((value = fcntl(fd,F_GETFL,0) < 0))
	{
		err_sys("fcntl F_GETFL error");
	}

	value |= flag;

	/* set file flag */
	if(fcntl(fd,F_SETFL,value) < 0)
	{
		err_sys("fcntl F_SETFL error");
	}
}
