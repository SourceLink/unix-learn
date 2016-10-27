#include "apue.h"
#include <fcntl.h>


#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int 
main(void)
{
	umask(0);   /* 不屏蔽设置权限 */

	if(creat("foo",RWRWRW) < 0){
		err_sys("creat error for foo");
	}
	
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* 屏蔽这些权限位 */

	if(creat("bar",RWRWRW) < 0){  		      /* 此时创建的文件访问权限部分被屏蔽即无法设置 */
		err_sys("creat error for bar");
	}
	
	exit(0);
}
