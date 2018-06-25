#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define MYPORT "3490"
#define BACKLOG 10

int main(void) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd, new_fd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status;
    status = getaddrinfo(NULL, MYPORT, &hints, &res);

    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (sockfd == -1) {
        perror("Socket error: ");
        return 1;
    }

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("Bind error: ");
        return 1;
    }

    if (listen(sockfd, BACKLOG) < 0) {
        perror("Listen error: ");
        return 1;
    }

    addr_size = sizeof(their_addr);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);


    // send and recv
    // int send(int sockfd, const void *msg, int len, int flags (set to 0))
    // returns the amount of bytes that were sent, -1 on error
    //
    // int recv(int sockfd, void *buf, int len, int flags)
    // returns number of bytes read into the buffer, -1 on error,
    // 0 on connection closed by remote

    // int sendto(int sockfd, const void *msg, int len, unsigned int flags,
    //            const struct sockaddr *to, socklen_t tolen)
    // same as send but if you want to send out of same socket to
    // multiple places

    // int recvfrom(int sockfd, void *buf, int len, unsigned int flags,
    //              const struct sockaddr *from, int fromlen)
    //
    // for tolen and fromlen use sizeof(*to/*from) or sizeof(struct
    // sockaddr_storage)

    // after all this sending and recving, close the socket
    close(sockfd);
    // or use shutdown(int sockfd, int how)
    // how = 0 (no more receiving), 1 (no more sending), 2 (no more anything,
    // same as close())
    // close() still must be called to free the descriptor

    // int getpeername(int sockfd, struct sockaddr *addr, int *addrlen);
    // addr holds information after call
    // int gethostname(char *hostname, size_t size);
    // hostname holds name after call, size is sizeof(hostname)
    
    
}
