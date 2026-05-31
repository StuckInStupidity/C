#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>

/*
#include <stdlib.h>
return EXIT_SUCCESS;   // same as return 0
return EXIT_FAILURE;   // same as return 1
*/

int fib(int x){
	if(x<=1) return x; 
	return fib(x-1) + fib(x-2);
}

int duper(char **argv, char *output){
	pid_t pid = fork();
	if(pid < 0) {printf("Something went wrong in duper.\n"); return 1;}
	else if(pid==0){
		FILE *file = fopen(output, "w");
		if(!file) exit(1);
		int fd = fileno(file); if(fd==-1) exit(1);
		int dt = dup2(fd, STDOUT_FILENO); if(dt<0) exit(1);
		fclose(file);
		execvp(argv[0], argv);
		exit(1);
	}
	else {
		int status; if(waitpid(-1, &status, 0)==-1) return -1; if(!WIFEXITED(status) || WEXITSTATUS(status) == 1) {printf("Something went wrong in duper.\n"); return 1;}
		printf("My child send me %d.\n", WEXITSTATUS(status)); return 0;
	}
}

int wait_pipe(int x){
	int pipefd[2];
	if (pipe(pipefd) == -1) err(EXIT_FAILURE, "pipe");
	//pipefd[0] -> read end
	//pipefd[1] -> write end
	//set child writes at [1] => parent reads at [0]

	pid_t pid = fork(); 
	// create new process -> memory duplication but own memory address space unlike threads that share heap and global variables but own stack space
	// closing unused pipes prevents deadlocks

	if(pid<0) return -1;
	else if(pid==0){
		if(close(pipefd[0]) == -1) err(EXIT_FAILURE, "close"); //this process doesnt read but write
		if(x < 0) exit(-1); //wraps at 255 !
		int f = fib(x);
		if(write(pipefd[1], &f, sizeof(int)) != sizeof(int)) err(EXIT_FAILURE, "write"); // != -1 => error in general
		if(close(pipefd[1]) == -1) err(EXIT_FAILURE, "close");
		exit(0); // _exit(EXIT_SUCCES)
	}
	else{
		if(close(pipefd[1]) == -1) err(EXIT_FAILURE, "close"); //this process doesnt write but read
		int status; //waitpid(pid_fils_wanted, &status, nb_options)
		if(waitpid(-1, &status, 0)==-1) return -1; //-1 attend tous les fils
		if(!WIFEXITED(status)) return -1;
		if(WEXITSTATUS(status)==255) return -1; //be careful returned code is an unsigned byte taking its value from 0 to 255, so -1 ==> 255
		int y;
		if(read(pipefd[0], &y, sizeof(int)) != sizeof(int)) return -1; // < 0 => error in general
		if(close(pipefd[0]) == -1) err(EXIT_FAILURE, "close");
		printf("My child knows how to count the Fibonacci sequence. He found %d for %d!\n",y,x);
		return 0;
	}
}

void buff(){
        int pipefd[2]; pipe(pipefd);
	char buf[] = "Hello from your child !\n";
        pid_t pid = fork();
        if(pid<0) {printf("an error occured\n"); return;}
        else if(pid==0){
                close(pipefd[0]);
                write(pipefd[1], buf, strlen(buf)*sizeof(char));
                close(pipefd[1]); exit(0);
        }
        else{
                close(pipefd[1]);
                int status; wait(&status);
                if(!WIFEXITED(status) || WEXITSTATUS(status)==255) {printf("an error occured\n"); return;}
		char *buff = calloc(strlen(buf)+1, 1);
                read(pipefd[0], buff, strlen(buf)*sizeof(char));
		buff[strlen(buf)] = '\0';
		printf("My child sends me : %s", buff);
                close(pipefd[0]); free(buff);
        }
}

void double(){
	int pipeA[2]; int pipeB[2]; // A : parent -> child, B : child -> parent
	pipe(pipeA); pipe(pipeB);
	pid_t pid = fork();
	if(pid==0) {
		close(pipeA[1]); close(pipeB[0]);
		while(1){
			int res; 
			ssize_t m = read(pipeA[0], &res, sizeof(int)); 
			if(m==0) {close(pipeA[0]); close(pipeB[1]); exit(0);}
			res*=res;
			write(pipeB[1], &res, sizeof(int));
		}
	} else{
		close(pipeA[0]); close(pipeB[1]);
		while(1){
			int cin; scanf("%d", &cin); 
			if(cin == -1) {close(pipeA[1]); close(pipeB[0]); return 0;}
			write(pipeA[1], &cin, sizeof(int));
			read(pipeB[0], &cin, sizeof(int));
			printf("The Oracle says the square is: %d\n", cin);
		}
	}
}
