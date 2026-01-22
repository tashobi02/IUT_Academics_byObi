#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Shared accounts
int A = 1000, B = 1000, C = 1000;

// Mutexes for each account
pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexC = PTHREAD_MUTEX_INITIALIZER;

/*
• Thread T1: Transfers 100 from A → B (10 times).
• Thread T2: Transfers 50 from B → C (20 times).
• Thread T3: Transfers 25 from C → A (40 times).
*/

// Utility function to print balances
void print_balances(const char* msg) {
    printf("%s | A=%d B=%d C=%d | Total=%d\n",
           msg, A, B, C, A + B + C);
}

// Thread T1: A -> B (100) x10
void* thread1(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutexA);
        pthread_mutex_lock(&mutexB);

        if (A >= 100) {
            A -= 100;
            B += 100;
            print_balances("T1: A -> B (100)");
        }

        pthread_mutex_unlock(&mutexB);
        pthread_mutex_unlock(&mutexA);

        usleep(100000);
    }
    return NULL;
}

// Thread T2: B -> C (50) x20
void* thread2(void* arg) {
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutexB);
        pthread_mutex_lock(&mutexC);

        if (B >= 50) {
            B -= 50;
            C += 50;
            print_balances("T2: B -> C (50)");
        }

        pthread_mutex_unlock(&mutexC);
        pthread_mutex_unlock(&mutexB);

        usleep(100000);
    }
    return NULL;
}

// Thread T3: C -> A (25) x40
void* thread3(void* arg) {
    for (int i = 0; i < 40; i++) {
        // IMPORTANT: lock A first, then C (global order)
        pthread_mutex_lock(&mutexA);
        pthread_mutex_lock(&mutexC);

        if (C >= 25) {
            C -= 25;
            A += 25;
            print_balances("T3: C -> A (25)");
        }

        pthread_mutex_unlock(&mutexC);
        pthread_mutex_unlock(&mutexA);

        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    print_balances("Initial");

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    print_balances("Final");

    return 0;
}
