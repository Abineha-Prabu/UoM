#ifndef EXAMPLE_COMP_SHM_H
#define EXAMPLE_COMP_SHM_H

#define SHM_NAME "/example.shm"

typedef struct {
    int param;
    int global;
    int result;
} shm_data_t;

#endif /* EXAMPLE_COMP_SHM_H */