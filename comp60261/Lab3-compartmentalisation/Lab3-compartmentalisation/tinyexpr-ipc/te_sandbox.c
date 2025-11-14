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

#define MAX_EXPR_LEN 4096

int main() {
    mkfifo(PARAM_PIPE, 0666);
    mkfifo(RESULT_PIPE, 0666);
    
    int param_fd, result_fd;

    // Open pipes once and keep open
    param_fd = open(PARAM_PIPE, O_RDONLY);
    result_fd = open(RESULT_PIPE, O_WRONLY);
    
    if (param_fd < 0 || result_fd < 0) {
        perror("Failed to open FIFO");
        return 1;
    }

    while(1) {
        int len;
        ssize_t n = read(param_fd, &len, sizeof(int));
        
        if (n == 0) break;           // EOF, client closed, exit
        if (n != sizeof(int)) continue; // corrupted read, skip
        
        if (len <= 0 || len > MAX_EXPR_LEN) {
            double dummy_result = 0.0;
            int error = 1;
            write(result_fd, &dummy_result, sizeof(double));
            write(result_fd, &error, sizeof(int));
            continue;
        }
        
        char expr[len + 1];
        if (read(param_fd, expr, len) != len) {
            int error = 1;
            double dummy_result = 0.0;
            write(result_fd, &dummy_result, sizeof(double));
            write(result_fd, &error, sizeof(int));
            continue;
        }
        expr[len] = '\0';

        int error = 0;
        double result = te_interp(expr, &error);

        write(result_fd, &result, sizeof(double));
        write(result_fd, &error, sizeof(int));
    }

    close(param_fd);
    close(result_fd);
    return 0;
}
