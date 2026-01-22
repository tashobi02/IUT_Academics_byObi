#include <stdio.h>
#include <pthread.h>
#include <semaphore.h> // Required for semaphores

int counter = 0; // Shared resource

sem_t sem; // Semaphore

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        sem_wait(&sem); // Enter critical section
        counter++;      // Critical section
        sem_post(&sem); // Exit critical section
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    // Initialize semaphore with value 1 (for mutual exclusion)
    sem_init(&sem, 0, 1); // Initialize semaphore

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem); // Cleanup

    printf("Final counter value: %d\n", counter);
    return 0;
}
