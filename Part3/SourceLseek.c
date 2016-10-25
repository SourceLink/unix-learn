#include "apue.h"
#include "fcntl.h"


/* 20161025 */

/*
 *when file is o_append lseek function can not set anywhere while you use write function on append
 *but read funciton can be read anywhere
 * */



int 
main(void){

	int fd = 0;
	int value = 0;
	char ReadArray[10] = {0};	

	if((fd = open("set_anywhere.txt",O_RDWR | O_CREAT | O_APPEND)) < 0){
		err_sys("open error");
	}
	/* set index */
	if(lseek(fd,10,SEEK_SET) == -1){
		err_sys("lseek error");
	}

	if(read(fd,ReadArray,10) != 10){
		err_sys("read error");
	}
	else{
		printf("ReadArray:%s\n",ReadArray);
	}
	
	if(lseek(fd,10,SEEK_SET) == -1){
		err_sys("lseek error");
	}

	if(write(fd,"hello word",10) != 10){
		err_sys("write error");
	}
	
	exit(0);
}

	
