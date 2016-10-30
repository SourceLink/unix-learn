#include "apue.h"
#include <fcntl.h>

/* 文件在进程没有结束前已经被删除，但所内容也就是文件所占的内存空间在进程结束后才被释放 */

int
main(void)
{
	if(open("de",O_RDWR) < 0){
		err_sys("open error");
	}

	if(unlink("de") < 0){
		err_sys("unlink error");
	}

	printf("file unlinked\n");

	sleep(15);
	
	printf("done\n");

	exit(0);
}
