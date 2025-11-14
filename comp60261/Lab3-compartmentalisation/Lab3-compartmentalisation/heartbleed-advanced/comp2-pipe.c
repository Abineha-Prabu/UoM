// Exercise part 2: this time the server lets the administrator initialise a
// hearbeat word that must be sent back to the client

// comp2-pipe.c: networking code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
    unsigned char buf[32];
    char heartbeat[32] = "heartbeat";  // default fallback
    int opt = 1;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fifo-path>\n", argv[0]);
        return 1;
    }

    const char *fifo = argv[1];

    // Open FIFO (blocks until comp1 writes)
    int fd = open(fifo, O_RDONLY);
    if (fd < 0) { perror("open fifo"); return 1; }

    ssize_t r = read(fd, heartbeat, sizeof(heartbeat) - 1);
    if (r <= 0) {
        perror("read fifo");
        close(fd);
        return 1;
    }
    heartbeat[r] = '\0';
    close(fd);

    // Networking code 
    int server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(12345),
        .sin_addr.s_addr = INADDR_ANY
    };

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 1);

    int client = accept(server, NULL, NULL);
    recv(client, buf, sizeof(buf), 0);

    int len = buf[1];   // Heartbleed vulnerability
    send(client, heartbeat, len, 0);

    close(client);
    close(server);

    return 0;
}

