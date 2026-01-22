#include <stdio.h>
#include <pthread.h>

#define HIST_SIZE 10
#define N 9
#define THREADS 2

int input[N] = {1, 3, 2, 5, 3, 7, 8, 3, 1};
int histogram[HIST_SIZE] = {0};

pthread_mutex_t mutex;

// Structure to pass range info to threads
typedef struct {
    int start;
    int end;
} ThreadData;

void* compute_histogram(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int local_hist[HIST_SIZE] = {0};

    // Step 1: Compute local histogram
    for (int i = data->start; i <= data->end; i++) {
        int val = input[i];
        local_hist[val]++;
    }

    // Step 2: Merge into global histogram (critical section)
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < HIST_SIZE; i++) {
        histogram[i] += local_hist[i];
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[THREADS];
    ThreadData ranges[THREADS];

    pthread_mutex_init(&mutex, NULL);

    // Compute ranges: split N elements as evenly as possible across THREADS
    int base = N / THREADS;  // minimum chunk size
    int extra = N % THREADS; // first 'extra' threads handle one more element
    int cursor = 0;
    for (int i = 0; i < THREADS; i++) {
        int count = base + (i < extra ? 1 : 0);
        ranges[i].start = cursor;
        ranges[i].end = cursor + count - 1; // inclusive end
        cursor += count;
    }

    // Create threads
    for (int i = 0; i < THREADS; i++) {
        pthread_create(&threads[i], NULL, compute_histogram, &ranges[i]);
    }

    // Join threads
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    // Print histogram
    int sum = 0;
    printf("Final Histogram:\n");
    for (int i = 0; i < HIST_SIZE; i++) {
        printf("histogram[%d] = %d\n", i, histogram[i]);
        sum += histogram[i];
    }

    printf("Sum of histogram values = %d\n", sum);
    return 0;
}
