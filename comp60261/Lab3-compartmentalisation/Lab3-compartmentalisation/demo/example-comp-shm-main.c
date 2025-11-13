#include "example-comp-shm.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>

int global;

int main() {
    shm_data_t *shared;
    int arg = 100;
    global = 50;
    char *password = "secret";
    
    // Create shm
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if(fd == -1) {
        printf("ERROR: cannot open shared memory fd\n");
        return -1;
    }

    shared = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(!shared) {
        printf("ERROR: cannot map shared memory area\n");
        return -1;
    }

    shared->param = arg;
    shared->global = global;

    // fork + exec library compartment
    pid_t pid = fork();

    if (pid == 0) {
        char *args[] = {"./te-comp", NULL};
        char *envp[] = {NULL};
        execve("./example-comp-pipe-lib", args, envp);
        return -1;
    }

    // give time for tbe library compartment to run the function and write
    // the result in shared memory
    usleep(200);

    printf("res: %d\n", shared->result);
    
    munmap(shared);
    close(fd);
    return 0;
}