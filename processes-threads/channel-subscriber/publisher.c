

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_SUBSCRIBERS 10

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Wrong number of arguments");
        exit(1);
    }

    int n = atoi(argv[1]);
    if (n <= 0 || n > MAX_SUBSCRIBERS) {
        perror("Wrong number of subscribers");
        exit(1);
    }

    char pipe_name[20];
    for (int i = 0; i < n; i++) {
        snprintf(pipe_name, sizeof(pipe_name), "/tmp/ex1/s%d", i);
        mkfifo(pipe_name, 0666); // give the permissions 0666
    }

    char message[1024];
    printf("Enter a message to publish: ");
    fgets(message, sizeof(message), stdin);

    for (int i = 1; i <= n; i++) {
        snprintf(pipe_name, sizeof(pipe_name), "/tmp/ex1/s%d", i);
        int fd = open(pipe_name, O_WRONLY);
        if (fd == -1) {
            perror("error related with open pipe");
            continue;
        }
        write(fd, message, sizeof(message));
        close(fd);
    }
}