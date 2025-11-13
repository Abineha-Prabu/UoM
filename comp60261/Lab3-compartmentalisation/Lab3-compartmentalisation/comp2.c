// Server with a heatbleed-like vulnerability leaking an administrator password
// trigger the exploit by launching the server and in another terminal:
// printf '\x01\x90hi' | nc localhost 12345
//
// The server can also take an optional command line parameter which value
// should be "login"
// It will then prompt for the administrator password and if authentication
// succeeds, it will run some privileged code before starting the server

// Compartment 2: networking server only

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(void) {

    unsigned char buf[32];
    int opt = 1;

    // Setup the server to listen to port 12345
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("socket");
        return 1;
    }

    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server);
        return 1;
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(12345),
        .sin_addr.s_addr = INADDR_ANY
    };

    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server);
        return 1;
    }

    if (listen(server, 1) < 0) {
        perror("listen");
        close(server);
        return 1;
    }

    printf("[comp2 %d] listening on port 12345\n", getpid());

    int client = accept(server, NULL, NULL);
    if (client < 0) {
        perror("accept");
        close(server);
        return 1;
    }

    ssize_t r = recv(client, buf, sizeof(buf), 0);
    if (r < 0) {
        perror("recv");
        close(client);
        close(server);
        return 1;
    }
    
    printf("[comp2 %d] recv returned %zd bytes: ", getpid(), r);
    for (ssize_t i = 0; i < r; ++i) {
        printf("%02x ", (unsigned char)buf[i]);
    }
    printf("\n");

    // Heartbleed-style vulnerability:
    // client sends: [type][len][data] -> respond with `len` bytes
   
    unsigned int len = 0;
    if (r >= 2) {
        len = (unsigned char)buf[1]; 
        printf("[comp2 %d] interpreted len=%u\n", getpid(), len);
    } else {
        printf("[comp2 %d] packet shorter than 2 bytes; nothing to send\n", getpid());
    }

    // Send response
    if (len > 0) {
        ssize_t s = send(client, buf + 2, len, 0);
        if (s < 0) {
            perror("send");
        } else {
            printf("[comp2 %d] send() returned %zd bytes\n", getpid(), s);
        }
    }

    // Cleanup
    close(client);
    close(server);

    return 0;
}
