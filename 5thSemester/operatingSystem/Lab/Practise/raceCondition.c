#include <stdio.h>
#include <pthread.h>

int counter = 0; // Shared resource

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        counter++; // Critical section
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    // two threads are running concurrently  - the main thread and the increment thread (t1)
    pthread_create(&t2, NULL, increment, NULL);
    // now three threads are running concurrently - the main thread, increment thread (t1) and increment thread (t2)
    pthread_join(t1, NULL);
    // this is a blocking call - the main thread will wait here until t1 finishes execution
    pthread_join(t2, NULL);
    // this is a blocking call - the main thread will wait here until t2 finishes execution
    printf("Final counter value: %d\n", counter);
    return 0;
}
