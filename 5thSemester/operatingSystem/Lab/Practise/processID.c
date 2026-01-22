#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // linux specific header for fork()

int main(int argc, char* argv[]) {
    int id = fork();
    printf("Current ID is %d\n", id);
    printf("My Process ID is %d\n", getpid());
    printf("My Parent Process ID is %d\n", getppid());
    if (id != 0) {
        wait(NULL);
    }
    return 0;
}