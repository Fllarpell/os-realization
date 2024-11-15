#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#define MEMORY_SIZE 10 * 1024 * 1024

int main() {
    struct rusage usage;

    for (int i = 0; i < 10; ++i) {
        void *memory = malloc(MEMORY_SIZE);
        if (memory == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        memset(memory, 0, MEMORY_SIZE);

        if (getrusage(RUSAGE_SELF, &usage) == 0) {
            printf("Memory usage: %ld kilobytes\n", usage.ru_maxrss);
        } else {
            perror("Failed to get memory usage");
        }

        sleep(1);
    }

    return 0;
}
