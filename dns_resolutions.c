#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hostname or IP>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *input = argv[1];
    struct addrinfo hints, *res, *p;
    struct sockaddr_in *ipv4;
    char ipstr[INET6_ADDRSTRLEN];

    // Zero out hints and set parameters for the lookup
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    // Get address info
    int status = getaddrinfo(input, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    printf("Host: %s\n", input);
    printf("IP addresses:\n");

    // Loop through all results
    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        // IPv4 or IPv6
        if (p->ai_family == AF_INET) { // IPv4
            ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // Convert the IP to a string
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("  %s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res);

    // Reverse lookup for IP address
    struct sockaddr_in sa;
    char host[NI_MAXHOST];

    inet_pton(AF_INET, input, &(sa.sin_addr));
    sa.sin_family = AF_INET;

    status = getnameinfo((struct sockaddr *)&sa, sizeof(sa), host, NI_MAXHOST, NULL, 0, 0);
    if (status != 0) {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    printf("Reverse lookup for IP %s: %s\n", input, host);

    return 0;
}