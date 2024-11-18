#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

void print_ip_addresses(struct addrinfo *res) {
    char ipstr[INET6_ADDRSTRLEN];
    for (struct addrinfo *p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        if (p->ai_family == AF_INET) { // IPv4
            addr = &((struct sockaddr_in *)p->ai_addr)->sin_addr;
            ipver = "IPv4";
        } else { // IPv6
            addr = &((struct sockaddr_in6 *)p->ai_addr)->sin6_addr;
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("  %s: %s\n", ipver, ipstr);
    }
}

void reverse_lookup(char *input) {
    struct sockaddr_in sa;
    char host[NI_MAXHOST];

    inet_pton(AF_INET, input, &sa.sin_addr);
    sa.sin_family = AF_INET;

    int status = getnameinfo((struct sockaddr *)&sa, sizeof(sa), host, NI_MAXHOST, NULL, 0, 0);
    if (status != 0) {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    printf("Reverse lookup for IP %s: %s\n", input, host);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hostname or IP>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *input = argv[1];
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(input, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    printf("Host: %s\n", input);
    printf("IP addresses:\n");
    print_ip_addresses(res);
    freeaddrinfo(res);

    reverse_lookup(input);

    return 0;
}
