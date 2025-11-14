#define SHM_LIB_BUILD
#include "custom_tinyexpr.h"
#include "tinyexpr.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/te_shm"

int main(void) {
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    te_shm_t *shm = mmap(NULL, sizeof(te_shm_t),
                         PROT_READ | PROT_WRITE,
                         MAP_SHARED, fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    while (1) {
        pthread_barrier_wait(&shm->barrier_req);   // wait for new expression
        shm->result = te_interp(shm->expression, &shm->error);
        pthread_barrier_wait(&shm->barrier_res);   // notify main
    }

    munmap(shm, sizeof(te_shm_t));
    return 0;
}

