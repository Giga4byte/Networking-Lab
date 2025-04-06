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

void receive_message (int server_socket) {
  char buffer[MAX_BUFFER_SIZE];
  int bytes_received = recv(server_socket, message, strlen(message), 0);
  if (bytes_received > 0) {
    buffer[bytes_received] = '\0';
    printf ("Server: %s\n", buffer);
  }
}

int main () {
  int server_socket;
  struct sockaddr_in server_addr;
  char buffer[MAX_BUFFER_SIZE];

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    printf("error in socket creation...\n");
    return -1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("error connecting...\n");
    return -1;
  }

  receive_message(server_socket);

  while (1) {
    printf("MENU OF COMMANDS\n: 1. MAIL FROM:\t2. RCPT TO:\n3. DATA\t4. QUIT\n");
    printf("Enter command: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    send_message(server_socket, buffer);
    receive_message(server_socket);

    if(strncmp(buffer, "DATA", 4) == 0) {
        printf("Enter email body ending with '.':\n");
        while (1) {
            fgets(buffer, MAX_BUFFER_SIZE, stdin);
            if(strcmp(buffer, ".\n") == 0) {
                send_message(server_socket, ".\r\n");
                break;
            } 
            send_message(server_socket, buffer);
        }
        receive_message (server_socket);
    }
    if (strncmp(buffer, "QUIT", 4) == 0) {
        break;
    }
  }
  close(server_socket);
  return 0;
}
