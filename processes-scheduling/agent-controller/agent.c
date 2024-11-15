#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_SIGUSR1() {
    FILE *textFile = fopen("text.txt", "r");

    if (textFile == NULL) {
        perror("Error opening text file");
        exit(1);
    }

    printf("OPENED FILE\n");
    char text[256];
    while (fgets(text, sizeof(text), textFile)) {
        printf("%s\n", text);
    }
    fclose(textFile);
}

void handle_SIGUSR2() {
    printf("Process terminating...\n");
    // unlink("/tmp/agent.pid");
    unlink("/var/run/agent.pid");
    exit(0);
}


int main(void) {
    // FILE *pidFile = fopen("/tmp/agent.pid", "w");
    FILE *pidFile = fopen("/var/run/agent.pid", "w");

    if (pidFile == NULL) {
        perror("error related with opening pid file");
        exit(1);
    }
    fprintf(pidFile, "%d\n", getpid());
    fclose(pidFile);

    signal(SIGUSR1, handle_SIGUSR1);
    signal(SIGUSR2, handle_SIGUSR2);


    while (1) {
        pause();
    }

    return 0;
}
