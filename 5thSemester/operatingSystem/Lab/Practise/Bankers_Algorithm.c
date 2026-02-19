#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 5 // Number of Processes
#define M 3 // Number of Resource Types

typedef struct {
    int allocation[N][M];
    int max[N][M];
    int available[M];
    int need[N][M];
} SystemState;

int count = 0;
int* isSafe(SystemState *state) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            state->need[i][j] = state->max[i][j] - state->allocation[i][j];
        }
    }
    bool finish[N] = {false};

    int work[M];
    for (int j = 0; j < M; j++) {
        work[j] = state->available[j];
    }

    int *safeSeq = (int*)malloc(sizeof(int) * N);
    count = 0;

    while (count < N) {
        bool found = false;

        for (int i = 0; i < N; i++) {

            if (!finish[i]) {

                bool possible = true;
                for (int j = 0; j < M; j++) {
                    if (state->need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < M; j++) {
                        work[j] += state->allocation[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    return safeSeq;
}

int main() {
    SystemState state = {
        .allocation = {
            {0, 1, 0},
            {2, 0, 0},
            {3, 0, 2},
            {2, 1, 1},
            {0, 0, 2}
        },
        .max = {
            {7, 5, 3},
            {3, 2, 2},
            {9, 0, 2},
            {2, 2, 2},
            {4, 3, 3}
        },

        .available = {3, 3, 2}   
    };

    int *safeSeq = isSafe(&state);

    if (count == N) {
        printf("System is SAFE.\nSequence: ");
        for (int i = 0; i < N; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is UNSAFE.\nSequence (partial): ");
        for (int i = 0; i < count; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    }

    free(safeSeq);
    return 0;
}
