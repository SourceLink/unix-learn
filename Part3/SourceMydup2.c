#include "apue.h"

/* 20161025 */

int MyDup2(int _fd,int _newfd);



int 
main(void){

	int fd = 0;
	
	fd = MyDup2(1,12);
	if(fd < 0){
		err_sys("MyDup2 error");
		exit(-1);
	}
	
	printf("fd = %d\n",fd);
	
	close(fd);
	
	exit(0);
}



int MyDup2(int _fd,int _newfd)
{
        int fdArray[_newfd];
        int index = 0;
        int newfdIndex = 0;

        /* assert _fd and _newfd */
        if(_fd < 0 || _fd > 255 ){
                printf("fd is woring");
                return -1;
        }

        if(_newfd < 0 || _newfd >255){
                printf("newfd is woring");
                return -1;
        }

        if(_fd = _newfd)
        {
                return _newfd;
        }
        else
        {
                close(_newfd);
        }

        /* dup is guaranteed to be the lowest-numbered available file descriptor */
        for(index = 0;index < _newfd;index++){
                if((fdArray[index] = dup(_fd)) < 0){
                        err_sys("dup error");
                }
                else if(fdArray[index] == _newfd){
                        newfdIndex = index;
                        break;  /* copy success */
		}
        }

        /* close other fd */
        index--;
        for(;index > 0;index--){
                close(fdArray[index]);
        }

        return fdArray[newfdIndex];
}

