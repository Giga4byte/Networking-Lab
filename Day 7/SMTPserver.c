// SMTP server code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

void send_message (int client_socket, const char *message) {
  send (client_socket, message, strlen(message), 0);
}

int main () {
  int server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[MAX_BUFFER_SIZE], sender[MAX_BUFFER_SIZE] = "", receiver[MAX_BUFFER_SIZE] = "", body[MAX_BUFFER_SIZE] = "";

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    
  }
}
