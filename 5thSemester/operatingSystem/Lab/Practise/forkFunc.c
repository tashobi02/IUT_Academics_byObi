#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // linux specific header for fork()

int main(int argc, char* argv[]) {
    int id = fork();
    printf("Hello World from id: %d\n", id);
    if (id == 0) {
        printf("Hello from child process\n");
    } else {
        printf("Hello from main process\n");
    }
    return 0;
}