// te_sandbox.c
#include "tinyexpr.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PARAM_PIPE "/tmp/te_param.pipe"
#define RESULT_PIPE "/tmp/te_result.pipe"

int main() {
    mkfifo(PARAM_PIPE, 0666);
    mkfifo(RESULT_PIPE, 0666);

    while(1) {
        int len;
        int recv_fd = open(PARAM_PIPE, O_RDONLY);
        if (read(recv_fd, &len, sizeof(int)) != sizeof(int)) break;

        char expr[len + 1];
        read(recv_fd, expr, len);
        expr[len] = '\0';
        close(recv_fd);

        int error = 0;
        double result = te_interp(expr, &error);

        int send_fd = open(RESULT_PIPE, O_WRONLY);
        write(send_fd, &result, sizeof(double));
        write(send_fd, &error, sizeof(int));
        close(send_fd);
    }

    return 0;
}

