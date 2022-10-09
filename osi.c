#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

enum
{
    DEC = 10
};

int
main(int argc, char *argv[])
{
    int count_of_process = 0;
    int N = strtol(argv[1], NULL, DEC) + 2;
    int all = argc;
    if (all > N) {
        all = N;
    }
    int status = 0;
    for (int i = 2; i < argc; ++i) {
        FILE *f = fopen(argv[i], "r");
        char name[PATH_MAX];
        int info = fscanf(f, "%s", name);
        if (info == 1) {
            pid_t pid;
            pid = fork();
            if (pid == 0) {
                execlp(name, name, NULL);
                _exit(1);
            } else if (i >= all && pid != 0) {
                wait(&status);
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    count_of_process++;
                }
            }
        fclose(f);
        }
    }
    while (wait(&status) > 0) {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            count_of_process++;
        }
    }
    printf("%d\n", count_of_process);
    return 0;
}
