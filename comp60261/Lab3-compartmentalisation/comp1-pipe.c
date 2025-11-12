// Exercise part 2: this time the server lets the administrator initialise a
// hearbeat word that must be sent back to the client
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_PATH "/tmp/heartbeat_fifo"

void privileged_function(char *heartbeat) {
    printf("Privileged code running!\n");

    // Set the heartbeat word
    printf("Enter the new value for the heartbeat word to send to the clients: ");
    if (fgets(heartbeat, 32, stdin) == NULL) {
        fprintf(stderr, "Error reading heartbeat\n");
        exit(1);
    }

    // remove carriage return
    size_t l = strlen(heartbeat);
    if (l > 0 && heartbeat[l-1] == '\n') heartbeat[l-1] = '\0';

    // more privilege operations...

    return;
}

int main(int argc, char **argv) {
    char admin_pw[64] = "supersecret";
    char attempt[128];
    char heartbeat[32];

    // initialise the heartbeat word to a default value
    strcpy(heartbeat, "heartbeat");

    if(argc == 2 && !strcmp(argv[1], "login")) {
        printf("Please enter the admin password: ");
        if (fgets(attempt, sizeof(attempt), stdin) == NULL) {
            fprintf(stderr, "Error reading password\n");
            return -1;
        }


        // remove carriage return
        size_t la = strlen(attempt);
        if (la > 0 && attempt[la-1] == '\n') attempt[la-1] = '\0';


        if (!strcmp(attempt, admin_pw)) {
            privileged_function(heartbeat);
            // create FIFO if it does not exist
            if (mkfifo(FIFO_PATH, 0600) == -1) {
                // if it already exists that's fine
                // otherwise warn but continue
            }
            
            // open FIFO for writing and write heartbeat
            int fd = open(FIFO_PATH, O_WRONLY);
            if (fd == -1) { perror("open fifo for write"); return 1; }
            
            // write null-terminated heartbeat
            if (write(fd, heartbeat, strlen(heartbeat) + 1) == -1) {
                perror("write fifo"); close(fd); return 1;
            }
            close(fd);
            
            // exec comp2; pass fifo path as argv[1]
            char *child_argv[] = {"./comp2-pipe", FIFO_PATH, NULL};
            extern char **environ;
            
            if (execve("./comp2-pipe", child_argv, environ) == -1) {
                perror("execve");
                return 1;
            }
            } else {
                printf("Admin authentication failed!\n");
                return -1;
            }
    }
    
    // fallback: run comp2 and use default heartbeat written to fifo
    if (mkfifo(FIFO_PATH, 0600) == -1) {
        // ignore
        }
    
    // write default heartbeat
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd != -1) {
        write(fd, "heartbeat\0", 10);
        close(fd);
    }
    char *child_argv[] = {"./comp2-pipe", FIFO_PATH, NULL};
    extern char **environ;
    if (execve("./comp2-pipe", child_argv, environ) == -1) {
        perror("execve");
        return 1;
    }
    return 0;
}
