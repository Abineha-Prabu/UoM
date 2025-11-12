// te_client.c
#include "custom_tinyexpr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


#define PARAM_PIPE "/tmp/te_param.pipe"
#define RESULT_PIPE "/tmp/te_result.pipe"

static int sandbox_pid = 0;

// spawn sandbox process
static void init_sandbox() {
    mkfifo(PARAM_PIPE, 0666);
    mkfifo(RESULT_PIPE, 0666);

    pid_t pid = fork();
    if (pid == 0) {
        execl("./te_sandbox", "./te_sandbox", NULL);
        exit(-1);
    }
    sandbox_pid = pid;
}

// client wrapper
double te_interp(const char *expr, int *error) {
    static int initialized = 0;
    if (!initialized) {
        init_sandbox();
        initialized = 1;
    }

    int len = strlen(expr);
    int send_fd = open(PARAM_PIPE, O_WRONLY);
    write(send_fd, &len, sizeof(int));
    write(send_fd, expr, len);
    close(send_fd);

    int recv_fd = open(RESULT_PIPE, O_RDONLY);
    double result;
    read(recv_fd, &result, sizeof(double));
    read(recv_fd, error, sizeof(int));
    close(recv_fd);

    return result;
}

