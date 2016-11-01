#include "apue.h"



static char fullpath[100] = "/home";

int 
main(void)
{
	struct stat statbuf;	
	
	int index = 0;	

	if(lstat(fullpath,&statbuf) < 0)
		err_sys("lstat error");
	else
		printf("lstat ok\n");

	index = strlen(fullpath);	

	fullpath[index++] = '/';
	fullpath[index] = 0;

	strcpy(&fullpath[index],"sourcelink");
	
	printf("str:%s\n",fullpath);
	
	if(lstat(fullpath,&statbuf) < 0)
		err_sys("/home/sourcelink lstat error");
	else
		printf("lsata ok\n");	
	
	exit(0);
}
