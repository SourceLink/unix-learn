#include <dirent.h>
#include "SourcePathalloc.c"


typedef int Myfunc(const char* ,const struct stat* , int );

static Myfunc myfunc;
static int dopath(Myfunc* );   /* 回调函数 */
static int myftw(char* ,Myfunc* );

static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;



int
main(int argc,char* argv[])
{
	int ret;
	
	if(argc != 2)
		err_quit("usage:ftw <starting-pathname>");

	ret  = myftw(argv[1],myfunc); 	/* does it all */
	
	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if(ntot == 0)
		ntot = 1;		/* avoid divide by 0;print 0 for all counts */
	printf("regular files = %7ld, %5.2f %%\n",nreg,nreg*100.0/ntot);
	
	printf("directories =%7ld, %5.2f %%\n",ndir,ndir*100.0/ntot);
	
	printf("block special =%7ld,%5.2f %%\n",nblk,nblk*100.0/ntot);

	printf("char special =%7ld,%5.2f %%\n",nchr,nchr*100.0/ntot);

	printf("FIFOS =%7ld,%5.2f %%\n",nfifo,nfifo*100.0/ntot);
	
	printf("sysmbolic links =%7ld,%5.2f% %%\n",nslink,nslink*100.0/ntot);
	
	printf("sockets =%7ld,%5.2f %%\n",nsock,nsock*100.0/ntot);	

	exit(ret);
}



#define FTW_F 1		/* file other than directory */
#define FTW_D 2		/* directory */
#define FTW_DNR 3	/* directory that can't be read */
#define FTW_NS 4	/* file that we can't stat */



static char* fullpath;
static size_t pathlen;



static int
myftw(char* pathname,Myfunc* func)	/* we return whatever func() returns */
{
	fullpath = path_alloc(&pathlen);	/* malloc PATHMAX+1 bytes */		
	if(pathlen <= strlen(pathname)){
		pathlen = strlen(pathname) * 2;
		/* adjust the size of memory */
		if((fullpath = realloc(fullpath,pathlen)) == NULL)
			err_sys("realloc failed");
	}
	
	strcpy(fullpath,pathname);
	return(dopath(func));
}

static int
dopath(Myfunc* func)	/* we return whathever func() returns */
{
	struct stat statbuf;
	struct dirent* dirp;
	DIR* dp;
	int ret,n;
	
	if(lstat(fullpath,&statbuf) < 0) 	/* stat error */
		return(func(fullpath,&statbuf,FTW_NS));
	if(S_ISDIR(statbuf.st_mode) == 0) 	/* not a directory */
		return(func(fullpath,&statbuf,FTW_F));

       /*
 	* It's a directory.first call func() for the directory,	
 	* then process each filename in the directory. 
 	*/
	
	if((ret = func(fullpath,&statbuf,FTW_D)) != 0)
		return(ret);
	n = strlen(fullpath);
	
	/* expand path buffer */
	if(n+ NAME_MAX + 2 > pathlen){
		pathlen *= 2;
		if((fullpath = realloc(fullpath,pathlen)) == NULL)
			err_sys("realloc failed");
	}
	
	fullpath[n++] = '/';
	fullpath[n] = 0;
	
	
	if((dp = opendir(fullpath)) == NULL)	/* can't read directory */
		return(func(fullpath,&statbuf,FTW_DNR));
	
	while((dirp = readdir(dp)) != NULL){
		if((strcmp(dirp->d_name,".") == 0) || (strcmp(dirp->d_name,"..") == 0))
			continue;		/* ignore dot and dot-dot */
		strcpy(&fullpath[n],dirp->d_name);/* append name after '/' */
		if((ret = dopath(func)) != 0)	/* recursive */
			break;
	}

	fullpath[n-1] = 0;	/* erase everthing from slash onward */
	
	if(closedir(dp) < 0)
		err_ret("can't close directory %s",fullpath);
	
	return(ret);
}



static int
myfunc(const char* pathname,const struct stat* statptr,int type)
{
	switch(type){
		case FTW_F:
			switch(statptr->st_mode & S_IFMT){
				case S_IFREG:	nreg++;	break;
				case S_IFBLK:	nblk++; break;
				case S_IFCHR:	nchr++; break;
				case S_IFIFO:   nfifo++; break;
				case S_IFLNK: 	nslink++; break;
				case S_IFSOCK:	nsock++; break;
				case S_IFDIR:	err_dump("for S_IFDIR for %s",pathname);
			}
		break;
		
		case FTW_D:
			ndir++;
		break;

		case FTW_NS:
			err_ret("stat error for %s",pathname);
		break;
		
		default:
			err_dump("unknow type %d for pathname %s",type,pathname);
		break;

	}
	
	return 0;
}
