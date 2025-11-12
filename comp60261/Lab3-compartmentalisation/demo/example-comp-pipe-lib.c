#include "example-comp-pipe.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int global;

int library_function(int *parameter) {
    char *cryptokey = "private";
    int ret = *parameter + global + 42;
    return ret;
}

int main() {
    int parameter;

    int recv_fd = open(PARAM_PIPE_PATH, O_RDONLY);
    int send_fd = open(RESULT_PIPE_PATH, O_WRONLY);

    if(recv_fd == -1 || send_fd == -1) {
        printf("ERROR: can't open pipe fds\n");
        return -1;
    }

    // read parameter and global
    if( read(recv_fd, &parameter, sizeof(int)) != sizeof(int) ||
        read(recv_fd, &global, sizeof(int)) != sizeof(int)) {
            printf("ERROR reading parameters\n");
            return -1;
    }

    // invoke library function
    int result = library_function(&parameter);

    // send result
    if(write(send_fd, &result, sizeof(int)) != sizeof(int)) {
        printf("ERROR: sending result\n");
        return -1;
    }

    close(recv_fd);
    close(send_fd);
    return 0;
}