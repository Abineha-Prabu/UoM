// Exercise part 2: this time the server lets the administrator initialise a
// hearbeat word that must be sent back to the client
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

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

    // initialising the heartbeat word to a default value
    strcpy(heartbeat, "heartbeat");

    if (argc == 2 && !strcmp(argv[1], "login")) {
        printf("Please enter the admin password: ");
        if (fgets(attempt, sizeof(attempt), stdin) == NULL) {
            fprintf(stderr, "Error reading password\n");
            return -1;
        }  

        // remove carriage return
        size_t la = strlen(attempt);
        if (la > 0 && attempt[la-1] == '\n') attempt[la-1] = '\0';

        if(!strcmp(attempt, admin_pw)){
            privileged_function(heartbeat);
            
            memset(admin_pw, 0, sizeof(admin_pw));

            
            // Prepare argv for execve: argv[0] comp2 program, argv[1] heartbeat
	    char *child_argv[] = {"./comp2-cmdline", heartbeat, NULL};
	    extern char **environ;

	    // executing compartment 2 with heartbeat as first argument
	    if (execve("./comp2-cmdline", child_argv, environ) == -1) {
	        perror("execve");
	        return 1;
	    }
	    // execve does not return on success
        }else {
            memset(admin_pw, 0, sizeof(admin_pw));
            printf("Admin authentication failed!\n");
            return -1;
        }

    }

    // If not invoked with login, behave like original (start server as-is)
    // fallbacks to exec comp2 with default heartbeat
    char *child_argv[] = {"./comp2-cmdline", "heartbeat", NULL};
    extern char **environ;
    if (execve("./comp2-cmdline", child_argv, environ) == -1) {
        perror("execve");
        return 1;
    }
    
    return 0;
}
