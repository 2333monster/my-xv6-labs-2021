#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <math.h>


void new_proc(int p[2]){
	int prime;
	int n;
	int flag;
	if(read(p[0],&prime,4) != 4){
		fprintf(2,"child process failed to read in prims");
		exit(1);
	}
	printf("prime %d\n",prime);

	flag = read(p[0],&n,4);
	if(flag){
		int newp[2];
		pipe(newp);
		if(fork() == 0){
			new_proc(newp);
		}else{
			if(n%prime)write(newp[1],&n,4);
			while(read(p[0],&n,4)){
				if(n%prime)write(newp[1],&n,4);
			}
			close(newp[1]);
			close(p[0]);
			wait(0);
		}
	}else{	
		exit(0);
	}
}

int 
main(int argc, char* argv[]){
	int p[2];
	pipe(p);
	if(fork() == 0){
		new_proc(p);
	}else{
		close(p[0]);
		for(int i = 2; i <= 35; i++){
			if(write(p[1],&i,4) != 4){
				fprintf(2,"first proc failed to write in primes");
				exit(1);
			}
		}
		wait(0);
		close(p[1]);
		exit(0);
	}
	return 0;
}
