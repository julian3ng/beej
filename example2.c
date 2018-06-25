#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// int socket(int domain, int type, int protocol)
// domain is PF_INET or PF_INET6
// type is SOCK_STREAM or SOCK_DGRAM
// protocol can be 0 to choose the proper protocol, or call
// getprotobyname("tcp"|"udp") to get the right number

// just get the values from your addrinfo struct

int main(int argc, char **argv) {
    int s;
    int status;
    struct addrinfo hints, *res;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((status = getaddrinfo("www.example.net", "http", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }


    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (s == -1) {
        perror("Socket error: ");
        return 1;
    }

    // bind binds a socket to a port on host machine, don't need if you're the
    // client
    // same as above but with
    // hints.ai_flags = AI_PASSIVE;
    // getaddrinfo(NULL, "3940", &hints, &res);
    // s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    // bind(s, res->ai_addr, res->ai_addrlen);

    // connect() will automatically bind a local port if we don't care about what
    // it is

    connect(s, res->ai_addr, res->ai_addrlen);

    // listen() is for listening for incoming connections :O
    // listen(int sockfd, int backlog)
    // backlog is the number of connections allowed on the incoming queue
    // you have to bind() before listen()ing
    // getaddrinfo() -> socket() -> bind() -> listen()

    // after listening, you must accept()
    // accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
    // addr is pointer to local struct sockaddr_storage, which holds
    // information about the incoming connection
    
}
