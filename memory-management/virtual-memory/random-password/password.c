#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define PASSWORD_LENGTH 8

void generate_password(char *password) {
    int randFile = open("/dev/urandom", O_RDONLY);
    if (randFile < 0) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }

    unsigned char random_bytes[PASSWORD_LENGTH - 5];
    if (read(randFile, random_bytes, sizeof(random_bytes)) < 0) {
        perror("Failed to read from /dev/urandom");
        close(randFile);
        exit(EXIT_FAILURE);
    }
    close(randFile);

    strcpy(password, "pass:");

    for (int i = 5; i < PASSWORD_LENGTH; ++i) {
        password[i] = (random_bytes[i - 5] % 94) + 33;
    }
    password[PASSWORD_LENGTH] = '\0';
}

int main() {
    FILE *pid_file = fopen("/tmp/ex1.pid", "w");
    if (!pid_file) {
        perror("Failed to open /tmp/ex1.pid");
        return EXIT_FAILURE;
    }
    fprintf(pid_file, "%d\n", getpid());
    fclose(pid_file);

    char *password = mmap(NULL, PASSWORD_LENGTH + 1, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (password == MAP_FAILED) {
        perror("mmap failed");
        return EXIT_FAILURE;
    }

    generate_password(password);

    printf("Password stored in memory: %s\n", password);

    while (1) {
        sleep(1);
    }

    return 0;
}
