#include "example-comp-pipe.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int global;

int main() {
    int arg = 100;
    global = 50;
    char *password = "secret";
    
    // Create pipes
    mkfifo(PARAM_PIPE_PATH, 0666);
    mkfifo(RESULT_PIPE_PATH, 0666);

    // fork + exec library compartment
    pid_t pid = fork();

    if (pid == 0) {
        char *args[] = {"./te-comp", NULL};
        char *envp[] = {NULL};
        execve("./example-comp-pipe-lib", args, envp);
        return -1;
    }

    // open pipe fds
    int send_fd = open(PARAM_PIPE_PATH, O_WRONLY);
    int recv_fd = open(RESULT_PIPE_PATH, O_RDONLY);

    if(recv_fd == -1 || send_fd == -1) {
        printf("ERROR: can't open pipe fds\n");
        return -1;
    }

    // send param then global
    if (write(send_fd, &arg, sizeof(int)) != sizeof(int) ||
        write(send_fd, &global, sizeof(int)) != sizeof(int)) {
            printf("ERROR: Can't write in pipe\n");
            return -1;
    }

    // read the result
    int result;
    if(read(recv_fd, &result, sizeof(int)) != sizeof(int)) {
        printf("ERROR: can't read result from pipe\n");
        return -1;
    }

    printf("res: %d\n", result);

    close(send_fd);
    close(recv_fd);
    return 0;
}