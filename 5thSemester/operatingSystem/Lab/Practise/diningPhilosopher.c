#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

// One counting semaphore for room capacity
sem_t room;

// One semaphore per fork
sem_t forks[N];

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Enter the room (max 4 philosophers)
        sem_wait(&room);

        // Pick up forks
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // Put down forks
        sem_post(&forks[right]);
        sem_post(&forks[left]);

        // Leave the room
        sem_post(&room);
    }
    return NULL;
}

int main() {
    pthread_t phil[N];
    int id[N];

    // Initialize room semaphore to 4
    sem_init(&room, 0, 4);

    // Initialize forks
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        id[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&phil[i], NULL, philosopher, &id[i]);
    }

    // Join threads (never ends)
    for (int i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }

    return 0;
}
