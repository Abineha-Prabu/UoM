// Server with a heatbleed-like vulnerability leaking an administrator password
// trigger the exploit by launching the server and in another terminal:
// printf '\x01\x90hi' | nc localhost 12345
//
// The server can also take an optional command line parameter which value
// should be "login"
// It will then prompt for the administrator password and if authentication
// succeeds, it will run some privileged code before starting the server

// compartment 1: authentication + privileged code, then fork/exec comp2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define COMP2_PATH "./comp2"

void privileged_function() {
    printf("Privileged code running!\n");
    // ... do some privilege stuff here e.g. update the server's configuration
    return;
}

int main(int argc, char **argv) {
    // Secret password only in compartment 1
    char admin_pw[64] = "supersecret"; // admin password

    if(argc == 2 && !strcmp(argv[1], "login")) {
        // Attempt at admin login

        // Get the password attempt
        printf("Please enter the admin password: ");
        fflush(stdout);
        char attempt[128];
        if (!fgets(attempt, sizeof(attempt), stdin)) {
            fprintf(stderr, "failed to read input\n");
            memset(admin_pw, 0, sizeof(admin_pw));
            return 1;
        }

        // remove carriage return
        size_t L = strlen(attempt);
        if (L > 0 && attempt[L - 1] == '\n') attempt[L - 1] = '\0';

        // check if the password is correct
        if(!strcmp(attempt, admin_pw))
            privileged_function();
        else {
            printf("Admin authentication failed!\n");
            memset(admin_pw, 0, sizeof(admin_pw));
            return -1;
        }
    }

    printf("[%d] compartment1: forking to launch compartment2 (%s)\n", getpid(), COMP2_PATH);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        memset(admin_pw, 0, sizeof(admin_pw));
        return 1;
    }

    if (pid == 0) {
    
        char *args[] = { COMP2_PATH, NULL };
        char *envp[] = { NULL };

        printf("[%d] compartment1(child): execve(%s)\n", getpid(), COMP2_PATH);
        execve(COMP2_PATH, args, envp);

        perror("execve");
        _exit(127);
    } else {

        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            memset(admin_pw, 0, sizeof(admin_pw));
            return 1;
        }

        printf("[%d] compartment1: comp2 (pid %d) terminated. ", getpid(), pid);
        if (WIFEXITED(status))
            printf("exit status=%d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("killed by signal %d\n", WTERMSIG(status));
        else
            printf("terminated abnormally\n");


        memset(admin_pw, 0, sizeof(admin_pw));
    }

    return 0;
}
