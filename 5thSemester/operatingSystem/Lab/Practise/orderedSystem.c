#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_comm, sem_ctrl;

void* power_thread(void* arg) {
    sleep(1); // simulate delayed random start
    printf("[Power Thread] Power Initialized. Signal sent.\n");

    sem_post(&sem_comm); // allow Communication to start
    return NULL;
}

void* comm_thread(void* arg) {
    printf("[Comm Thread] Waiting for Signal...\n");
    sem_wait(&sem_comm); // wait for Power

    sleep(1); // simulate delay
    printf("[Comm Thread] Communication Initialized. Signal sent.\n");

    sem_post(&sem_ctrl); // allow Control to start
    return NULL;
}

void* control_thread(void* arg) {
    printf("[Control Thread] Waiting for Signal...\n");
    sem_wait(&sem_ctrl); // wait for Communication

    sleep(1); // simulate delay
    printf("[Control Thread] Control System Initialized.\n");
    return NULL;
}

int main() {
    pthread_t power, comm, control;

    sem_init(&sem_comm, 0, 0);
    sem_init(&sem_ctrl, 0, 0);

    // start threads in random order
    pthread_create(&control, NULL, control_thread, NULL);
    pthread_create(&comm, NULL, comm_thread, NULL);
    pthread_create(&power, NULL, power_thread, NULL);

    pthread_join(power, NULL);
    pthread_join(comm, NULL);
    pthread_join(control, NULL);

    sem_destroy(&sem_comm);
    sem_destroy(&sem_ctrl);

    return 0;
}
