#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 100

typedef struct Thread {
    pthread_t id;
    int i;
    char message[256];
} Thread;

pthread_mutex_t lock;

void *thread_function(void *arg) {
    Thread *t = (Thread *)arg;

    pthread_mutex_lock(&lock);

    printf("Thread %d is created\n", t->i);
    printf("Thread ID: %p, Message: %s\n", t->id, t->message);

    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Wrong number of arguments");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0 || n > MAX_THREADS) {
        perror("Wrong number of threads");
        return 1;
    }

    Thread threads[n];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < n; i++) {
        threads[i].i = i;
        snprintf(threads[i].message, sizeof(threads[i].message), "Hello from thread %d", i);

        if (pthread_create(&threads[i].id, NULL, thread_function, &threads[i]) != 0) {
            perror("Unsuccessful creating a thread");
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i].id, NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}

