#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


#ifndef WWPATH
#define WWPATH "/ilab/users/anp156/CS214/Assignment 3/ww"
#endif


int main(int argc, char* argv[]){
	int stats = 0;
	struct stat s;
	int fd[2];
	pid_t child;
	int i = 2;
	pipe(fd);
	
	
	while(i < argc){
		if(stat(argv[i], &s) == 0){
   			if(!(S_ISDIR(s.st_mode))){
				child = fork();
			}
		}
		//printf("%d\n", child);
		if(child == 0){
			
			close(fd[0]);
			//dup2(fd[1], 1);
			
			execl(WWPATH,WWPATH, argv[1], argv[i], NULL);
			return EXIT_FAILURE;
			
		}else{

			
	
			i++;
			//printf("hey\n");
			close(fd[1]);

			//read from fd[0] what ww wrote to std out
			char arr[100];
			read(fd[0],arr, 100);

			close(fd[0]);
			wait(NULL); // not done
			if(stat(argv[i], &s) == 0){
   				if(!(S_ISDIR(s.st_mode))){
					printf("\n");
				}else{
					stats = 1;
				}
			}
			int status;
			if(waitpid(child,&status,0) == -1){
				stats = 1;
			}
			if(WIFEXITED(status)!=0){
				int a = WEXITSTATUS(status);
				if(a !=0){
					stats = 1;
				}
			}
		

		}
		//printf("%d\n", stats);
		
	}
	
	if(stats != 0){
		//printf("hi\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

	/*

			int status;
			if(waitpid(child,&status,0) == -1){
				//return EXIT_FAILURE;
			}
			
			if(WIFEXITED(status)){
				const int ex = WEXITSTATUS(status);
				
				if(ex != 0){
					stats = 1;
				}
			}
	
	int i = 2;
	pid_t child;
	while(i < argc){
		child = fork();
		if(child == 0){
			
			i++;

		}else{
			
			execl(WWPATH,WWPATH, argv[1], argv[i], NULL);
			return EXIT_SUCCESS;
				
			

		}
		

	}*/
	

}
