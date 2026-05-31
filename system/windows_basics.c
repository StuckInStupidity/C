#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <windows.h>
#include <direct.h>
#include <io.h> 
#include <string.h>

void print_env_settings(int argc, char* argv[], char* envp[]) {
    int i;
    char* login = getenv("USERNAME");
    printf("Connecte sous le nom de %s\n", login);
    printf("\nAppel avec %d parametres\n", argc);
    printf("\nNom de la commande : %s\n", argv[0]);
    printf("\nArguments de la commande : \n");
    for (i = 1; i < argc; i++) printf("%s ", argv[i]);
    printf("\nVariables environnements :\n");
    for (i = 0; envp[i] != NULL; i++) printf("%s\n", envp[i]);
}

void test_env_modification(void) {
    _putenv("MODE=DEBUG");  // Windows equivalent of setenv
    printf("MODE = %s\n", getenv("MODE"));

    _putenv("MODE=");       // Remove variable
    printf("MODE removed\n");
}

void print_cwd(void) {
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)))
        printf("Current directory: %s\n", cwd);
}

void print_process_info(void) {
    printf("PID  = %lu\n", GetCurrentProcessId());
    printf("PPID = (not directly available on Windows)\n");
    //PGID not applicable on windows
}

void list_dir(const char *path) {
    char searchPath[MAX_PATH];
    WIN32_FIND_DATAA data;

    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

    HANDLE h = FindFirstFileA(searchPath, &data);
    if (h == INVALID_HANDLE_VALUE) {
        printf("Cannot open directory: %s\n", path);
        return;
    }

    do {
        printf("%s\n", data.cFileName);
    } while (FindNextFileA(h, &data));

    FindClose(h);
}

void file_info(const char *path) {
    WIN32_FILE_ATTRIBUTE_DATA info;

    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &info)) {
        printf("Cannot stat file: %s\n", path);
        return;
    }

    unsigned long long size = ((unsigned long long)info.nFileSizeHigh << 32) | info.nFileSizeLow;

    printf("Size: %llu bytes\n", size);

    if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) printf("Type: directory\n");
    else printf("Type: regular file\n");
}

void print_system_info(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    printf("CPU architecture: %u\n", si.wProcessorArchitecture);
    printf("Number of CPUs: %u\n", si.dwNumberOfProcessors);
}

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

void setup_signal_handler(void) {
    signal(SIGINT, handler);  // Works for Ctrl+C
}
