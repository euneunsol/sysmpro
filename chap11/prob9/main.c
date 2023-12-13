#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void alarmHandler(int signo);

int main() {
    struct sigaction sa;
    sa.sa_handler = alarmHandler;
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    alarm(5);

    while (1) {
        for (int i = 1; i <= 4; i++) {
            sleep(1);
            printf("%d second\n", i);
        }
    }

    printf("No\n");
}

void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);
}

