#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CLIENTS 6
#define SERVER_CAPACITY 3

sem_t serverSlots;
pthread_mutex_t lock;
int status[NUM_CLIENTS] = {0};
int running = 1;

void* client_thread(void* arg) {
    int id = *(int*)arg;

    // Request server access
    sem_wait(&serverSlots);

    // Mark status = True
    pthread_mutex_lock(&lock);
    status[id] = 1;
    pthread_mutex_unlock(&lock);

    // Simulate processing time
    sleep(1);

    // Mark status = False
    pthread_mutex_lock(&lock);
    status[id] = 0;
    pthread_mutex_unlock(&lock);

    // Release slot
    sem_post(&serverSlots);

    return NULL;
}

void* monitor_thread(void* arg) {
    while (running) {
        pthread_mutex_lock(&lock);
        for (int i = 0; i < NUM_CLIENTS; i++) {
            printf("C%d=%s ", i + 1, status[i] ? "True" : "False");
        }
        printf("\n");
        pthread_mutex_unlock(&lock);

        usleep(500000); // print every 0.5 sec
    }
    return NULL;
}

int main() {
    pthread_t clients[NUM_CLIENTS], monitor;
    int ids[NUM_CLIENTS];

    sem_init(&serverSlots, 0, SERVER_CAPACITY);
    pthread_mutex_init(&lock, NULL);

    // Start monitor
    pthread_create(&monitor, NULL, monitor_thread, NULL);

    // Start clients
    for (int i = 0; i < NUM_CLIENTS; i++) {
        ids[i] = i;
        pthread_create(&clients[i], NULL, client_thread, &ids[i]);
        usleep(100000); // small stagger to simulate near-simultaneous arrival
    }

    // Wait for clients to finish
    for (int i = 0; i < NUM_CLIENTS; i++)
        pthread_join(clients[i], NULL);

    running = 0;
    pthread_join(monitor, NULL);

    sem_destroy(&serverSlots);
    pthread_mutex_destroy(&lock);

    return 0;
}
