#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>

char** split(char* line){
	char delimiter[] = " \n\t"; char **res = NULL; int cnt = 0;
	char *token = strtok(line, delimiter);
	while(token!=NULL){
		char** temp = realloc(res, (cnt+2)*sizeof(char*)); //verif if realloc fails (if !res) => free from res[0] to res[cnt-1]
		res = temp;
		res[cnt] = strdup(token); //verif if !res[cnt] => free from res[0] to res[cnt-1]
		token = strtok(NULL, delimiter); cnt++;
	}
	if(cnt==0) res = malloc(sizeof(char*));
	res[cnt] = NULL;
	return res;
}

int exec_cmd(char** args){
	pid_t pid = fork();
	if(pid<0) return -1;
	else if(pid==0){
		execvp(args[0], args);
		exit(255);
	}
	else{
		int status; if(waitpid(-1, &status, 0)==-1) return -1; if(!WIFEXITED(status) || WEXITSTATUS(status) == 255) return -1;
		return WEXITSTATUS(status);
	}
}

int execution_loop(){
	char *line = NULL; size_t n = 0, last = 0;
	while(getline(&line, &n, stdin) != -1){
		char **tokens = split(line);
		if(!tokens[0]) printf("Unknown command\n"); //if user press enter line not empty = "\n" and tok[0]=NULL and will fail strcmp
		//maybe just continue instead of unknown print
		else if(strcmp(tokens[0], "exit") == 0) {
			if(tokens[1]) last = atoi(tokens[1]);
			for(int i=0;tokens[i];i++) free(tokens[i]); 
			free(tokens); free(line); return last;
		}
		else if(strcmp(tokens[0], "run") == 0) last = exec_cmd(&tokens[1]);
		else if(strcmp(tokens[0], "?") == 0) printf("%d\n", last);
		else printf("Unknown command\n");
		for(int i=0;tokens[i];i++) free(tokens[i]); free(tokens);
	}
	//case of getline error or Ctrl + D / EOF
	free(line); return 0;
}

/* use the following function to detect whether the program is running in an interactive terminal (user) or not (automated script/moulinette).
This allows to print a prompt (like > or $ ) to stdout before reading input only when a real user is interacting with the program.
int is_terminal()
{
    return isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
}
if (is_terminal()) printf("21sh$ "); */