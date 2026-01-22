#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_nav;    // Signal from Fuel -> Navigation
sem_t sem_launch; // Signal from Navigation -> Launch

void* fuel_thread(void* arg) {
    sleep(1); // simulate work
    printf("[Fuel Thread] Fuel system activated. Signal sent.\n");
    sem_post(&sem_nav); // allow navigation to start
    return NULL;
}

void* navigation_thread(void* arg) {
    printf("[Navigation Thread] Waiting for fuel system...\n");
    sem_wait(&sem_nav); // wait for fuel
    sleep(1);
    printf("[Navigation Thread] Navigation system online. Signal sent.\n");
    sem_post(&sem_launch); // allow launch
    return NULL;
}

void* launch_thread(void* arg) {
    printf("[Launch Thread] Waiting for navigation system...\n");
    sem_wait(&sem_launch); // wait for navigation
    sleep(1);
    printf("[Launch Thread] Launch sequence initiated!\n");
    return NULL;
}

int main() {
    pthread_t fuel, navigation, launch;

    // Initialize semaphores to 0 (locked)
    sem_init(&sem_nav, 0, 0);
    sem_init(&sem_launch, 0, 0);

    // Create threads in ANY order (result will still be sequenced)
    pthread_create(&launch, NULL, launch_thread, NULL);
    pthread_create(&navigation, NULL, navigation_thread, NULL);
    pthread_create(&fuel, NULL, fuel_thread, NULL);

    // Wait for all threads
    pthread_join(fuel, NULL);
    pthread_join(navigation, NULL);
    pthread_join(launch, NULL);

    sem_destroy(&sem_nav);
    sem_destroy(&sem_launch);

    return 0;
}
