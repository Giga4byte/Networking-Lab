# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>

# define MAX_BUFFER_SIZE 1024
# define PORT 8001

void send_message (int server_socket, const char *message) {
  send (server_socket, message, strlen(message), 0);
}

void receive_message (int server_socket, const char *message) {
  char buffer[MAX_BUFFER_SIZE];
  int bytes_received = recv(server_socket, message, strlen(message), 0);
  if (bytes_received > 0) {
    buffer[bytes_received] = '\0';
    printf ("Server: %s\n", buffer);
  }
}

int main () {
  int server_socket;
}
