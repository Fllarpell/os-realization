#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(void) {
    // FILE *pidFile = fopen("/tmp/agent.pid", "r");
    FILE *pidFile = fopen("/var/run/agent.pid", "r");
    pid_t pid;
    if (pidFile == NULL) {
        perror("Error opening PID file");
        return 1;
    }

    if (fscanf(pidFile, "%d", &pid) != 1) {
        fclose(pidFile);
        perror("Error: No agent found");
        return 1;
    }
    fclose(pidFile);
    printf("PID: %d\n", pid);

    printf("Agent found.\n");

    char commandLine[256];
    while (1) {
        printf("Choose a command {“read”, “exit”, “stop”, “continue”} to send to the agent: ");

        if (scanf("%s", commandLine) == EOF) {
            kill(pid, SIGTERM);
            break;
        }

        if (strcmp(commandLine, "read") == 0) {
            kill(pid, SIGUSR1);
        } else if (strcmp(commandLine, "exit") == 0) {
            kill(pid, SIGUSR2);
            break;
        } else if (strcmp(commandLine, "stop") == 0) {
            kill(pid, SIGSTOP);
        } else if (strcmp(commandLine, "continue") == 0) {
            kill(pid, SIGCONT);
        } else {
            printf("Invalid command.\n");
        }
    }




    return 0;
}