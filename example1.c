#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/* addrinfo {
 *     int ai_flags // AI_PASSIVE, AI_CANONNAME, etc.
 *     int ai_family // AF_INET, AF_INET6, AF_UNSPEC
 *     int ai_socktype // SOCK_STREAM, SOCK_DGRAM
 *     int ai_protocol // 0 for "any"
 *     size_t ai_addrlen // size of ai_addr in bytes
 *     struct sockaddr *ai_addr // struct sockaddr_in or _in6
 *     char *ai_canonname // full canonical hostname
 *     struct addrinfo *ai_next // next node
 * }
 */ 

int main(int argc, char **argv) {
    struct addrinfo hints, *res;
    int status;

    char ipstr[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr, "usage: showip hostname\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP Addresses for %s:\n\n", argv[1]);

    struct addrinfo *p;
    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("    %s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res);

    return 0;
}
