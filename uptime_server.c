#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <sys/sysinfo.h>
#include <unistd.h>

int main(void)
{
    printf("Uptime server version 0.1\n");

    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo * res;
    int retval = getaddrinfo(NULL, "8081", &hints, &res);
    if (retval != 0) {
        fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(retval));
        exit(EXIT_FAILURE);
    }

    int sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sfd == -1) {
        freeaddrinfo(res);
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    printf("sa_data: %s %d\n", res->ai_addr->sa_data, res->ai_addrlen);

    freeaddrinfo(res);

    const int listen_backlog = 10;
    if (listen(sfd, listen_backlog) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Listening...\n");

    while (1) {
        struct sockaddr peer_addr;
        socklen_t peer_addr_size = sizeof peer_addr;
        int cfd = accept(sfd, &peer_addr, &peer_addr_size);
        if (cfd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        struct sysinfo info;
        sysinfo(&info);
        char buf[80];
        sprintf(buf, "%ld", info.uptime);
        send(cfd, buf, strlen(buf), 0);
        puts(buf);

        close(cfd);
    }
    close(sfd);

    return 0;
}

/*
code inspired by:
Hands-On Network Programming with C, Lewis Van Winkle, 2019
man7 documentation
The Linux Programming Interface, Michael Kerrisk, 2010
*/

