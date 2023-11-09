#include "../kernel/types.h"
#include "../user/user.h"

char buf[1024];
int fd;
int
main(int argc, char* argv[]){
	fd = open(argv[2],0);
	read(fd,buf,sizeof(buf));
	write("output.txt",buf,sizeof(buf));
	return 0;
}	
