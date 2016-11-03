#include "apue.h"
#include <dirent.h>


int 
main(void)
{
	DIR* 	dp;
	struct dirent* dirp;	

	if((dp = opendir("/home/sourcelink")) == NULL)
		err_sys("opendir error");

	while((dirp = readdir(dp)) != NULL){
		
		if((strcmp(dirp->d_name,".") == 0) || (strcmp(dirp->d_name,"..") == 0))
			continue;
		printf("readdir:%s\n",dirp->d_name);
	}	

	exit(0);

}
