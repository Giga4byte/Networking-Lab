// SMTP server code
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define PORT 8001

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
    printff("error in socket creation...\n");
    return -1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_address)) < 0) {
    printf("error in binding...\n");
    return -1;
  }

  if (listen(server_socket, 10) < 0) {
    printf("error in listening...\n");
    return -1;
  }

  while (1) { // major
    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if (client_socket < 0) {
        printf("error in accepting...\n");
        return -1;
    }

    send_message(client_socket, "Hello from server. Server is ready\r\n");

    while (1) { // minor
        memset (buffer, 0, MAX_BUFFER_SIZE);
        int bytes_recv = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
        if (bytes_recv <= 0) {
            printf("connection disabled...\n");
            break;
        }

        buffer[bytes_recv] = '\0';
        printf("Received: %s", buffer);

        if (strncmp(buffer, "MAIL FROM:", 10) == 0) {
            sscanf(buffer, "MAIL FROM:<%s>", sender);
            send_message(client_socket, "sender mail id\r\n");
        } else if (strncmp(buffer, "RCPT TO:", 8) == 0) {
            sscanf(buffer, "RCPT TO:<%s>", receiver);
            send_message(client_socket, "receiver mail id\r\n");
        } else if (strncmp(buffer, "DATA", 4) == 0) {
            send_message(client_socket, "start mail input, end with <CRLF>.<CRLF>\r\n");
            memset(body, 0, MAX_BUFFER_SIZE);

            while (1) { // inside minor
                memset(buffer, 0, MAX_BUFFER_SIZE);
                bytes_recv = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
                if (bytes_recv <= 0) {
                    printf("information disabled...\n");
                    break;
                }
                buffer[bytes_recv] = '\0';

                if(strcmp(buffer, ".\r\n") == 0) {
                    break;
                }

                strcat(body, buffer);
            } // while inside minor

            send_message(client_socket, "message for delivery\r\n");
            printf("MAIL RECEIVED\nFROM: %s\nTO: %s\n BODY: %s\n", sender, receiver, body);
        } else if (strncmp(buffer, "QUIT", 4) == 0) {
            send_message(client_socket, "bye...\r\n");
            break;
        } else {
            send_message(client_socket, "command unrecognized\r\n");
        }
    } // while minor
    close(client_socket);
  } // while major
  close(server_socket);
  return 0;
}
