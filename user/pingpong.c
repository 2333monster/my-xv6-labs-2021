#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[]){
	int pid;
	int fd[2];
	pipe(fd);

	if(fork() == 0){
		pid = getpid();
		char buf[2];
		if(read(fd[0],buf,1)!=1){
			fprintf(2, "failed to read in child\n");
			exit(1);
		}
		close(fd[0]);
		printf("%d : receives ping\n",pid);
		if(write(fd[1],buf,1) != 1){
			fprintf(2, "failed to write in child\n");
			exit(1);
		}
		close(fd[1]);
		exit(0);
	}else{
		pid = getpid();
		char buf[2];
		char info[2] = "a";
		if(write(fd[1],info,1)!=1){
			fprintf(2, "failed to write in parent\n");
			exit(1);
		}
		close(fd[1]);
		wait(0);
		if(read(fd[0], buf, 1) != 1){
			fprintf(2, "failed to read from child\n");
			exit(1);
		}
		printf("%d : receives pong\n",pid);
		close(fd[0]);
		exit(0);
	}
}
