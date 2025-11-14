#ifndef CUSTOM_TINYEXPR_H
#define CUSTOM_TINYEXPR_H

#define _POSIX_C_SOURCE 200112L  

#include <pthread.h>   
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

/* Initialization / cleanup */
void te_init_shm(void);
void te_cleanup_shm(void);

/* Expression evaluation via SHM */
double te_interp_shm(const char *expression, int *error);
 
#ifndef SHM_LIB_BUILD
#define te_interp te_interp_shm
#endif

#endif /* CUSTOM_TINYEXPR_H */

