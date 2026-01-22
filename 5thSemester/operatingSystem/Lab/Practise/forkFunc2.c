#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // linux specific header for fork()

int main(int argc, char* argv[]) {
    int id = fork();
    int n;
    if (id == 0) {
        n = 1;
    } else {
        n = 6;
    }
    if (id != 0) {
        // wait();
    }
    int i;
    for (i = n; i < n + 5; i++) {
        printf("Process ID: %d, i = %d\n", getpid(), i);
        fflush(stdout);
    }
    printf("\n");

    return 0;
}
