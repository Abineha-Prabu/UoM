#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
    unsigned char buf[32];
    char heartbeat[512];
    int opt = 1;

    strcpy(heartbeat, "heartbeat");

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fifo-path>\n", argv[0]);
        return 1;
    }

    const char *fifo = argv[1];

    // open fifo for reading (blocks until writer exists)
    int fd = open(fifo, O_RDONLY);
    if (fd == -1) { perror("open fifo"); return 1; }

    ssize_t r = read(fd, heartbeat, sizeof(heartbeat)-1);
    if (r <= 0) { perror("read fifo"); close(fd); return 1; }
    heartbeat[r] = '\0';
    close(fd);

    // truncate heartbeat to 31 bytes
    char hb_small[32];
    strncpy(hb_small, heartbeat, sizeof(hb_small)-1);
    hb_small[31] = '\0';

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

    int len = buf[1]; // Heartbleed-style: no bounds check
    send(client, hb_small, len, 0);

    close(client);
    close(server);

    return 0;
}

