#include "SourcePathalloc.c"




int
main(void)
{
	char* ptr;
	size_t size;
	
	if(chdir("/home/sourcelink") < 0)
		err_sys("chdir error");
	
	ptr = path_alloc(&size);
	if(getcwd(ptr,size) == NULL)
		err_sys("getcwd failed");

	printf("cwd = %s\n",ptr);
	
	exit(0);
}
