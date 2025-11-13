#include "custom_tinyexpr.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define SHM_NAME "/te_shm"

static te_shm_t *shm = NULL;
static pid_t lib_pid = 0;

void te_init_shm() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(te_shm_t));
    shm = mmap(NULL, sizeof(te_shm_t),
               PROT_READ | PROT_WRITE,
               MAP_SHARED, fd, 0);

    pthread_barrierattr_t attr;
    pthread_barrierattr_init(&attr);
    pthread_barrierattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_barrier_init(&shm->barrier_req, &attr, 2);
    pthread_barrier_init(&shm->barrier_res, &attr, 2);

    // fork + exec library compartment
    lib_pid = fork();
    if(lib_pid == 0) {
        char *args[] = {"./shm-lib", NULL};
        char *envp[] = {NULL};
        execve("./shm-lib", args, envp);
        _exit(1);
    }
    // give time for lib to start
    usleep(1000);
}

// function to evaluate expression via SHM
double te_interp_shm(const char *expr, int *err) {
    strcpy(shm->expression, expr);
    pthread_barrier_wait(&shm->barrier_req);   // notify lib
    pthread_barrier_wait(&shm->barrier_res);   // wait for result
    *err = shm->error;
    return shm->result;
}

