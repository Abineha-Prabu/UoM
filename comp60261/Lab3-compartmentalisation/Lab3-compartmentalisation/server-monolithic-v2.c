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
    fgets(heartbeat, 32, stdin);

    // remove carriage return
    heartbeat[strlen(heartbeat)-1] = '\0';

    // more privilege operations...

    return;
}

int main(int argc, char **argv) {
    char admin_pw[64] = "supersecret";
    unsigned char buf[32];
    char heartbeat[32];
    int opt = 1;

    // initialise the heartbeat word to a default value
    strcpy(heartbeat, "heartbeat");

    if(argc == 2 && !strcmp(argv[1], "login")) {
        char attempt[128];

        printf("Please enter the admin password: ");
        fgets(attempt, 128, stdin);

        // remove carriage return
        attempt[strlen(attempt)-1] = '\0';

        if(!strcmp(attempt, admin_pw))
            privileged_function(heartbeat);
        else {
            printf("Admin authentication failed!\n");
            return -1;
        }

    }

    int server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(12345),
        .sin_addr.s_addr = INADDR_ANY
    };

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 1);

    int client = accept(server, NULL, NULL);

    recv(client, buf, sizeof(buf), 0);

    // Heartbleed-style vulnerability:
    // client sends: [type][len][data] -> respond with `len` bytes
    int len = buf[1];  // vulnerable: no bounds check

    // Send back the heartbeat word
    send(client, heartbeat, len, 0);

    close(client);
    close(server);

    return 0;
}