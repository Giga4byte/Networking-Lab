#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in address, client_addr;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER_SIZE] = {0};
    char response[MAX_BUFFER_SIZE];

    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        printf("Enter the string (or 'exit' to quit): ");
        scanf(" %s", response); 

        if (strcmp(response, "exit") == 0) {
            printf("EXITING FROM THE CHAT!\n");
            break;
        }

        int n;
        socklen_t client_len = sizeof(client_addr);
        n = recvfrom(server_fd, (char *)buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);

        sendto(server_fd, (const char *)response, strlen(response), 0, (const struct sockaddr *)&client_addr, client_len);
        printf("Response sent to client: %s\n", response);
    }

    close(server_fd);
    return 0;
}
