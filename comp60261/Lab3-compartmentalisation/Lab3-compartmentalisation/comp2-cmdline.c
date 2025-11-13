// Exercise part 2: this time the server lets the administrator initialise a
// hearbeat word that must be sent back to the client
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char **argv) {
    unsigned char buf[32];
    char heartbeat[32];
    int opt = 1;

    // initialise the heartbeat word to a default value
    strcpy(heartbeat, "heartbeat");

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <heartbeat>\n", argv[0]);
        return 1;
    }

    // copy heartbeat passed from comp1; ensure null-terminated
    strncpy(heartbeat, argv[1], sizeof(heartbeat)-1);
    heartbeat[sizeof(heartbeat)-1] = '\0';

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) { perror("socket"); return 1; }
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(12345),
        .sin_addr.s_addr = INADDR_ANY
    };

    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); return 1; }
    if (listen(server, 1) < 0) { perror("listen"); return 1; }

    int client = accept(server, NULL, NULL);
    if (client < 0) { perror("accept"); return 1; }

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
