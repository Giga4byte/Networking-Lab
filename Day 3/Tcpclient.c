#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8000
#define SERVER_ADDRESS "127.0.0.1"

int main() {
  // initialise sock, valread, serv_addr, message, buffer
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char *message = "Hello from client!";
  char buffer[1024] = {0};
  
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\nsocket creation error...\n");
    return -1;
  }
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  
  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, SERVER_ADDRESS, &serv_addr.sin_addr) <= 0) {
    printf("\ninvalid address/address not supported...\n");
    return -1;
  }
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nconnection failed...\n");
    return -1;
  }
  
  send(sock, message, strlen(message), 0);
  printf("Status: message sent\n");
  valread = read(sock, buffer, 1024);
  printf("Server: %s\n", buffer);
  return 0;
}
