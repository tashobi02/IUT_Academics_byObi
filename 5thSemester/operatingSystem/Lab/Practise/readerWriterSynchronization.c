#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0;
int read_count = 0;

sem_t mutex;       // protects read_count
sem_t write_block; // blocks writers/readers

void* reader(void* arg) {
    int id = *(int*)arg;
    printf("[Reader %d] Waiting to read...\n", id);

    // Entry section
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&write_block); // first reader blocks writers
    }
    sem_post(&mutex);

    // Critical section (reading)
    printf("[Reader %d] Reading data: %d\n", id, data);
    sleep(1);

    // Exit section
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&write_block); // last reader allows writers
    }
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    printf("[Writer %d] Waiting to write...\n", id);

    sem_wait(&write_block); // Writer gets exclusive access

    // Critical section (writing)
    printf("[Writer %d] Writing data...\n", id);
    data++;
    sleep(1);
    printf("[Writer %d] Updated data to %d\n", id, data);

    sem_post(&write_block);

    return NULL;
}

int main() {
    pthread_t r[3], w[1];
    int r_id[3] = {1, 2, 3};
    int w_id[1] = {1};

    sem_init(&mutex, 0, 1);
    sem_init(&write_block, 0, 1);

    // Start threads in mixed order to simulate randomness
    pthread_create(&r[0], NULL, reader, &r_id[0]);
    pthread_create(&r[1], NULL, reader, &r_id[1]);
    pthread_create(&w[0], NULL, writer, &w_id[0]);
    sleep(1); // delay to simulate next arrivals
    pthread_create(&r[2], NULL, reader, &r_id[2]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    pthread_join(w[0], NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_block);

    return 0;
}
