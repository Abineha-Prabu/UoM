// Server with a heatbleed-like vulnerability leaking an administrator password
// trigger the exploit by launching the server and in another terminal:
// printf '\x01\x90hi' | nc localhost 12345
//
// The server can also take an optional command line parameter which value
// should be "login"
// It will then prompt for the administrator password and if authentication
// succeeds, it will run some privileged code before starting the server

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void privileged_function() {
    printf("Privileged code running!\n");
    // ... do some privilege stuff here e.g. update the server's configuration
    return;
}

int main(int argc, char **argv) {
    char admin_pw[64] = "supersecret"; // admin password
    unsigned char buf[32];
    int opt = 1;

    if(argc == 2 && !strcmp(argv[1], "login")) {
        // Attempt at admin login

        // Get the password attempt
        printf("Please enter the admin password: ");
        char attempt[128];
        fgets(attempt, 128, stdin);

        // remove carriage return
        attempt[strlen(attempt)-1] = '\0';

        // check if the password is correct
        if(!strcmp(attempt, admin_pw))
            privileged_function();
        else {
            printf("Admin authentication failed!\n");
            return -1;
        }
    }

    // Setup the server to listen to port 12345
    int server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(12345),
        .sin_addr.s_addr = INADDR_ANY
    };

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 1);

    // Wait for a client's request
    int client = accept(server, NULL, NULL);

    // read the request into buf
    recv(client, buf, sizeof(buf), 0);

    // Heartbleed-style vulnerability:
    // client sends: [type][len][data] -> respond with `len` bytes
    int len = buf[1];  // vulnerable: no bounds check

    // Send response
    send(client, buf + 2, len, 0);

    // Cleanup
    close(client);
    close(server);

    return 0;
}