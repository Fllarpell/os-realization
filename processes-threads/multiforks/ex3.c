
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("No arguments");
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("--------------------\nPROCESS INFO: CHILD_ID: %d, PARENT_ID: %d \n--------------------\n", getpid(), getppid());
            sleep(5);
            return 0;
        } else {
            printf("--------------------\nPROCESS INFO: MAIN PROCESS: %d \n--------------------\n", getpid());

            sleep(5);
        }
    }

    return 0;
}

