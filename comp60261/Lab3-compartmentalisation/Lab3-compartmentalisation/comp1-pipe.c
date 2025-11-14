#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>

#define FIFO_PATH "/tmp/heartbeat_fifo"

void privileged_function(char *heartbeat) {
    printf("Privileged code running!\n");
    printf("Enter the new value for the heartbeat word to send to the clients: ");
    if (fgets(heartbeat, 32, stdin) == NULL) {
        fprintf(stderr, "Error reading heartbeat\n");
        exit(1);
    }

    // Remove trailing newline
    size_t l = strlen(heartbeat);
    if (l > 0 && heartbeat[l-1] == '\n') heartbeat[l-1] = '\0';
}

int main(int argc, char **argv) {
    char admin_pw[64] = "supersecret";
    char attempt[128];
    char heartbeat[32];

    strcpy(heartbeat, "heartbeat");  // default heartbeat

    if(argc == 2 && !strcmp(argv[1], "login")) {
        printf("Please enter the admin password: ");
        if (fgets(attempt, sizeof(attempt), stdin) == NULL) {
            fprintf(stderr, "Error reading password\n");
            return -1;
        }

        size_t la = strlen(attempt);
        if (la > 0 && attempt[la-1] == '\n') attempt[la-1] = '\0';

        if (!strcmp(attempt, admin_pw)) {
            privileged_function(heartbeat);

            // create FIFO if it does not exist
            if (mkfifo(FIFO_PATH, 0600) == -1 && errno != EEXIST) {
                perror("mkfifo");
                return 1;
            }

            // fork to start comp2 first
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                return 1;
            }

            if (pid == 0) {
                // child process: exec comp2
                char *child_argv[] = {"./comp2-pipe", FIFO_PATH, NULL};
                extern char **environ;
                execve("./comp2-pipe", child_argv, environ);
                perror("execve child");
                exit(1);
            } else {
                // parent: open FIFO and write heartbeat
                int fd = open(FIFO_PATH, O_WRONLY);
                if (fd == -1) {
                    perror("open fifo for write");
                    return 1;
                }
                write(fd, heartbeat, strlen(heartbeat) + 1);
                close(fd);

                // wait for child to replace itself
                wait(NULL);
            }

        } else {
            printf("Admin authentication failed!\n");
            return -1;
        }
    } else {
        // fallback: use default heartbeat
        if (mkfifo(FIFO_PATH, 0600) == -1 && errno != EEXIST) { }
        int fd = open(FIFO_PATH, O_WRONLY | O_NONBLOCK);
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
    }

    return 0;
}

