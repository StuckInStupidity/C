#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void print_env_settings(int argc, char* argv[], char* envp[]) {
	int i;
	char* login;
	login = getenv("LOGNAME"); //"USERNAME" for windows
	printf("Connecte sous le nom de %s\n", login);
	printf("\nAppel avec %d parametres\n", argc);
	printf("\nNom de la commande : %s\n", argv[0]);
	printf("\nArguments de la commande : \n");
	for (i = 1;i < argc;i++) printf("%s", argv[i]);
	printf("\nVariables environnements :\n");
	for (i = 0;envp[i] != NULL;i++) printf("%s\n", envp[i]);
}

void test_env_modification(void) {
    setenv("MODE", "DEBUG", 1);
    printf("MODE = %s\n", getenv("MODE"));

    unsetenv("MODE");
    printf("MODE removed\n");
}

/*
int setenv(const char *name, const char *value, int overwrite) -> ajoute une variable d'environnement name en l'initialisant à la valeur value.
Si elle existe déjà, sa valeur est mise à jour ssi overwrite et non nul.
void unsetenv(const char *name)
*/

void print_cwd(void) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) printf("Current directory: %s\n", cwd);
}

void print_process_info(void) {
    printf("PID  = %d\n", getpid());
    printf("PPID = %d\n", getppid());
    printf("PGID = %d\n", getpgrp());
}

void list_dir(const char *path) {
    DIR *d = opendir(path);
    if (!d) return;

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) printf("%s\n", entry->d_name);

    closedir(d);
}

void file_info(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) return;

    printf("Size: %ld bytes\n", st.st_size);

    if (S_ISREG(st.st_mode)) printf("Type: regular file\n");
    if (S_ISDIR(st.st_mode)) printf("Type: directory\n");
}

void print_system_info(void) {
    struct utsname u;
    if (uname(&u) == -1) return;

    printf("System: %s\n", u.sysname);
    printf("Node:   %s\n", u.nodename);
    printf("Kernel: %s\n", u.release);
    printf("Arch:   %s\n", u.machine);
}

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

void setup_signal_handler(void) {
    signal(SIGINT, handler);
}
