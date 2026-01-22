#include <stdio.h>
#include <pthread.h>

int counter = 0;      // Shared resource
pthread_mutex_t lock; // Mutex

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock); // Enter critical region
        counter++;
        pthread_mutex_unlock(&lock); // Exit critical region
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL); // Initialize mutex

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock); // Destroy mutex

    printf("Final counter value: %d\n", counter);
    return 0;
}
