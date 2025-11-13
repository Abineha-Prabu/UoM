#include "example-comp-shm.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>

int global;

int library_function(int *parameter) {
    char *cryptokey = "private";
    int ret = *parameter + global + 42;
    return ret;
}

int main() {
    shm_data_t *shared;

    // Attach to shared memory
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);

    shared = mmap(NULL, sizeof(shm_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(!shared) {
        printf("ERROR: cannot map shared memory area\n");
        return -1;
    }

    // set global's value
    global = shared->global;

    // invoke library function
    shared->result = library_function(&(shared->param));

    munmap(shared, sizeof(shm_data_t));
    close(fd);
    return 0;
}