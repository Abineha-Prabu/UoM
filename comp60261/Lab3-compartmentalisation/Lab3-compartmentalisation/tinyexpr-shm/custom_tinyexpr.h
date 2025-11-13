#ifndef CUSTOM_TINYEXPR_H
#define CUSTOM_TINYEXPR_H

#define _POSIX_C_SOURCE 200112L  // <<< ensure barriers are defined

#include <pthread.h>   // must be **before** any struct using pthread_barrier_t
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_EXPR_SIZE 4096

typedef struct {
    pthread_barrier_t barrier_req;   /* main -> lib: new request available */
    pthread_barrier_t barrier_res;   /* lib  -> main: result available */
    char expression[MAX_EXPR_SIZE];  /* expression string buffer */
    double result;                   /* result of evaluation */
    int error;                       /* error code */
} te_shm_t;

double te_interp(const char *expression, int *error);

#endif /* CUSTOM_TINYEXPR_H */

