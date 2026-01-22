#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Global configuration pointer
int* active_config = NULL;

// Single mutex (only one allowed)
pthread_mutex_t config_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Reader thread */
void* reader(void* arg) {
    int id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&config_mutex);

        // Guaranteed safe access
        if (active_config != NULL) {
            printf("Reader %d reads config value: %d\n",
                   id, *active_config);
        }

        pthread_mutex_unlock(&config_mutex);

        sleep(1);
    }
    return NULL;
}

/* Updater thread */
void* updater(void* arg) {
    int value = 100;

    while (1) {
        pthread_mutex_lock(&config_mutex);

        // Free old configuration
        free(active_config);

        // Allocate new configuration
        active_config = malloc(sizeof(int));

        // Invariant: active_config != NULL
        *active_config = value++;

        printf("Updater installed new config value: %d\n",
               *active_config);

        pthread_mutex_unlock(&config_mutex);

        sleep(3);
    }
    return NULL;
}

int main() {
    pthread_t r1, r2, r3, up;
    int id1 = 1, id2 = 2, id3 = 3;

    // Initial configuration (invariant must hold)
    active_config = malloc(sizeof(int));
    *active_config = 42;

    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&r3, NULL, reader, &id3);
    pthread_create(&up, NULL, updater, NULL);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(up, NULL);

    return 0;
}
