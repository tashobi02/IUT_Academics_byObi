#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t hReady;
sem_t hQueue;
sem_t oQueue;
sem_t barrier;

void* hydrogen(void* arg) {
    printf("H Ready\n");

    // Signal availability
    sem_post(&hReady);

    // Wait until selected for bonding
    sem_wait(&hQueue);

    // Barrier: wait for other atoms
    sem_wait(&barrier);

    printf("H Bonded\n");
    return NULL;
}

void* oxygen(void* arg) {
    printf("O Ready\n");

    // Wait for two hydrogen atoms
    sem_wait(&hReady);
    sem_wait(&hReady);

    // Release exactly two hydrogens
    sem_post(&hQueue);
    sem_post(&hQueue);

    // Barrier release: 3 atoms total
    sem_post(&barrier);
    sem_post(&barrier);
    sem_post(&barrier);

    printf("Bond Formed!\n");
    return NULL;
}

int main() {
    pthread_t h[4], o[2];

    sem_init(&hReady, 0, 0);
    sem_init(&hQueue, 0, 0);
    sem_init(&oQueue, 0, 0);
    sem_init(&barrier, 0, 0);

    // Create Hydrogen threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&h[i], NULL, hydrogen, NULL);
        sleep(1);
    }

    // Create Oxygen threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&o[i], NULL, oxygen, NULL);
        sleep(2);
    }

    for (int i = 0; i < 4; i++)
        pthread_join(h[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(o[i], NULL);

    return 0;
}
