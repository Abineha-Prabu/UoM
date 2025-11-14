// Exercise part 2: this time the server lets the administrator initialise a
// hearbeat word that must be sent back to the client

// comp1-pipe.c: authentication and privileged code
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>

#define FIFO_PATH "/tmp/heartbeat_fifo"

extern char **environ;

void privileged_function(char *heartbeat) {
    printf("Privileged code running!\n");
    
    // Set the heartbeat word
    printf("Enter the new value for the heartbeat word to send to the clients: ");

    fgets(heartbeat, 32, stdin);

    // remove carriage return
    heartbeat[strlen(heartbeat)-1] = '\0';

    // more privilege operations...

    return;
}


int main(int argc, char **argv) {
    char admin_pw[64] = "supersecret";
    char attempt[128];
    char heartbeat[32] = "heartbeat";   // default heartbeat

    // Authenticating admin
    if (argc == 2 && !strcmp(argv[1], "login")) {

        printf("Please enter the admin password: ");
        if (!fgets(attempt, sizeof(attempt), stdin)) {
            fprintf(stderr, "Failed reading password\n");
            return 1;
        }

	// remove carriage return
        size_t la = strlen(attempt);
        if (la > 0 && attempt[la-1] == '\n')
            attempt[la-1] = '\0';

        if (!strcmp(attempt, admin_pw)) {
            privileged_function(heartbeat);
        } else {
            printf("Admin authentication failed!\n");
            return -1;
        }
    }

    // Ensure FIFO exists
    if (mkfifo(FIFO_PATH, 0600) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    // Fork comp2
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child executes comp2
        char *child_argv[] = {"./comp2-pipe", FIFO_PATH, NULL};
        execve("./comp2-pipe", child_argv, environ);
        perror("execve");
        exit(1);
    }

    // Parent writes heartbeat to FIFO
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd < 0) {
        perror("open FIFO for writing");
        return 1;
    }

    write(fd, heartbeat, strlen(heartbeat) + 1);
    close(fd);

    // Waiting for comp2 to finish 
    wait(NULL);

    return 0;
}

