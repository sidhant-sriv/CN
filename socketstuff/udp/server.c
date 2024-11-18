// Get libraries
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
  // Create socket

  int sock;
  char buffer[1024];
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_len;

  // Initialize server address and port
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
  {
    printf("Error creating socket\n");
    exit(1);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(5000);
  if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    printf("Error binding\n");
    exit(1);
  }
  printf("Server is running\n");
  while (1)
  {
    addr_len = sizeof(client_addr);
    int n = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_len);
    if (n < 0)
    {
      printf("Error receiving data\n");
      exit(1);
    }
    buffer[n] = '\0';
    printf("Client: %s\n", buffer);
    sendto(sock, buffer, n, 0, (struct sockaddr *)&client_addr, addr_len);
  }
  close(sock);
  return 0;
}