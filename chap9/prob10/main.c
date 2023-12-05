#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 10

int main() {
    char *args[MAXARG];
    char input[256];
    char *token;
    int is_background;

    while (1) {
        printf("Pls input cmd : ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Parent process end\nExit\n");
            exit(0);
        }

        input[strlen(input) - 1] = '\0';

        int i = 0;
        is_background = 0;

        token = strtok(input, " \n");
        while (token != NULL && i < MAXARG - 1) {
            if (strcmp(token, "&") == 0) {
                is_background = 1;
                break;
            }
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                exit(1);
            }
        } else {
            printf("[%d] Parent process start\n", getpid());

            if (is_background) {
                printf("[%d] child process start\n", pid);
                sleep(1);
            }

            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf("Parent process end\nExit\n");
                exit(1);
            }

            if (!is_background) {
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    printf("SUCCESS\n\n");
                } else {
                    printf("FAILED\n\n");
                }
            } else {
                waitpid(pid, &status, WNOHANG);
                printf("[%d] child process end %d\n", getpid(), pid);
                printf("SUCCESS\n\n");
            }
        }
    }

    return 0;
}

