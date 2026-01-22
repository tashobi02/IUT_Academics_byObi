#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX 10

pthread_mutex_t mutex;

char high_buffer[MAX][50];
char low_buffer[MAX][50];
int high_count = 0, low_count = 0;

void* log_thread(void* arg) {
    char* msg = (char*)arg;
    pthread_mutex_lock(&mutex);

    if (msg[0] == 'H') {                            // High priority message flag
        strcpy(high_buffer[high_count++], msg + 2); // skip "H:"
    } else {
        strcpy(low_buffer[low_count++], msg + 2); // skip "L:"
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;

    pthread_mutex_init(&mutex, NULL);

    // Priority-tagged messages as per input
    pthread_create(&t1, NULL, log_thread, "L:Network OK");
    pthread_create(&t2, NULL, log_thread, "H:Disk Failure");
    pthread_create(&t3, NULL, log_thread, "L:User Login");
    pthread_create(&t4, NULL, log_thread, "H:Power Surge");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    // Buffer dump respecting priority
    printf("----- Buffer Dump -----\n");
    for (int i = 0; i < high_count; i++)
        printf("[HIGH] %s\n", high_buffer[i]);

    for (int i = 0; i < low_count; i++)
        printf("[LOW] %s\n", low_buffer[i]);

    pthread_mutex_destroy(&mutex);
    return 0;
}
