#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    printf("Client is running\n");
    int sock;
    char buffer[1024];
    struct sockaddr_in server_addr;

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server address

    // Send message to server
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Receive response from server
    socklen_t addr_len = sizeof(server_addr);
    int n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
    if (n < 0)
    {
        perror("Receive failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';
    printf("Server replied: %s\n", buffer);

    close(sock);
    return 0;
}