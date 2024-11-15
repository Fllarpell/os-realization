

#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void) {
    clock_t start_time;
    pid_t pid1, pid2;

    start_time = clock();

    pid1 = fork();

    if (pid1 == 0) {
        printf("PROCESS 1, CHILD_ID: %d, PARENT_ID: %d \n", getpid(), getppid());
        printf("EXECUTION_TIME FOR PROCESS 1: %f ms\n", (float)(clock() - start_time) / CLOCKS_PER_SEC * 1000);
    } else {
        pid2 = fork();

        if (pid2 == 0) {
            printf("PROCESS 2, CHILD_ID: %d, PARENT_ID: %d \n", getpid(), getppid());
            printf("EXECUTION_TIME FOR PROCESS 2: %f ms\n", (float)(clock() - start_time) / CLOCKS_PER_SEC * 1000);
        } else {
            printf("MAIN PROCESS, ID: %d \n", getpid());
        }
    }

    printf("TIME EXECUTION: %.2f ms\n", (float)(clock() - start_time) / CLOCKS_PER_SEC * 1000);

    return 0;
}
