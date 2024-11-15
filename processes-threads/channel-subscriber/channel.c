

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int pipefd[2];
    pid_t pid;
    char message[1024];

    if (pipe(pipefd) == -1) {
        perror("Error with pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("Error with fork");
        exit(1);
    }

    if (pid == 0) {
        close(pipefd[1]);
        read(pipefd[0], message, sizeof(message));
        printf("Message from parent process (publisher): %s\n", message);
    } else {
        close(pipefd[0]);
        printf("Enter the message: ");
        fgets(message, sizeof(message), stdin);
        write(pipefd[1], message, sizeof(message));
        close(pipefd[1]);
    }

    return 0;
}
