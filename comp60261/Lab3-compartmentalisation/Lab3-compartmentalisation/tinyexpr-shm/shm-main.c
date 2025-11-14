#define _POSIX_C_SOURCE 200112L

#include "custom_tinyexpr.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

#define SHM_NAME "/te_shm"

static te_shm_t *shm = NULL;
static pid_t lib_pid = 0;

void te_init_shm(void) {
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
    if (lib_pid == 0) {
        // In library process
        execl("./shm-lib", "./shm-lib", NULL);
        _exit(1);
    }

    // wait a tiny bit for shm-lib to start
    usleep(10000);
}

// Function to evaluate expression via SHM
double te_interp_shm(const char *expr, int *err) {
    strcpy(shm->expression, expr);
    pthread_barrier_wait(&shm->barrier_req);   // notify lib
    pthread_barrier_wait(&shm->barrier_res);   // wait for result
    *err = shm->error;
    return shm->result;
}

void te_cleanup_shm(void) {
    if (lib_pid > 0) {
        kill(lib_pid, SIGTERM);
        waitpid(lib_pid, NULL, 0);
    }
    if (shm) {
        munmap(shm, sizeof(te_shm_t));
        shm_unlink(SHM_NAME);
    }
}

/* Automatically initialize SHM before main() */
__attribute__((constructor))
static void init_te_shm_before_main(void) {
    te_init_shm();
}

/* Automatically cleanup SHM after exit */
__attribute__((destructor))
static void cleanup_te_shm_after_main(void) {
    te_cleanup_shm();
}

