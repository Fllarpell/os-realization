#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Wrong number of arguments");
        exit(1);
    }

    char pipe_name[20];
    snprintf(pipe_name, sizeof(pipe_name), "/tmp/ex1/s%s", argv[1]);
    int fd = open(pipe_name, O_RDONLY);
    if (fd == -1) {
        perror("error related with open pipe");
        exit(1);
    }

    char message[1024];
    read(fd, message, sizeof(message));
    printf("Message received: %s\n", message);
    close(fd);

    return 0;
}
