
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run_command(char *command) {
    char *args[1024];
    char *split_args = strtok(command, " \n");
    int i = 0;

    while (split_args != NULL) {
        args[i++] = split_args;
        split_args = strtok(NULL, " \n");
    }

    if (args[0] == NULL) {
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("error relates with fork");
        exit(1);
    }

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("error during execution of the command");
            exit(1);
        }
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char command[1024];

    while (1) {
        printf("shell_line>> ");
        if (fgets(command, 1024, stdin) == NULL) {
            break;
        }
        run_command(command);
    }

    return 0;
}
