#define _POSIX_C_SOURCE 199309L

#include "custom_tinyexpr.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double native(void) {
    return sqrt(pow(5, 2) + pow(7, 2) + pow(11, 2) + pow(8 - 2, 2));
}

int main(int argc, char *argv[]) {
    const char *expr = "sqrt(5^2+7^2+11^2+(8-2)^2)";
    long iterations = 100000;

    if (argc > 1)
        iterations = atol(argv[1]);

    struct timespec start, end;
    double result = 0.0;

    // Compute tinyexpr performance
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long i = 0; i < iterations; ++i){
        int err;
        result = te_interp(expr, &err);
        if(err) {
            printf("ERROR during benchmark.\n");
            return -1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    // Compute native performance
    clock_gettime(CLOCK_MONOTONIC, &start);

    volatile double native_result = 0.0;
    for (long i = 0; i < iterations; ++i) {
        native_result = native();
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double native_elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Expression: %s\n", expr);
    printf("Evaluated result: %.10f\n", result);
    printf("Native result: %.10f\n", native_result);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Evaluations per second: %.0f\n",
           iterations / elapsed);
    printf("Native total time: %.6f seconds\n", native_elapsed);
    printf("Native evaluations per second: %.0f\n",
           iterations / native_elapsed);

    return 0;
}
