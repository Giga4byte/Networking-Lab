#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8000
#define SERVER_ADDRESS "127.0.0.1"
#define MAX_BUFFER_SIZE 1024
#define TIMEOUT 2 // seconds

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client!";
    char buffer[MAX_BUFFER_SIZE] = {0};
    char *ack = "ACK";
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nsocket creation error...\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, SERVER_ADDRESS, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/address not supported...\n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed...\n");
        return -1;
    }

    // Stop and Wait Protocol
    while (1) {
        // Send message to server
        send(sock, message, strlen(message), 0);
        printf("Message sent to server\n");

        // Wait for acknowledgment with timeout
        fd_set readfds;
        struct timeval timeout;
        timeout.tv_sec = TIMEOUT;
        timeout.tv_usec = 0;

        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);

        int activity = select(sock + 1, &readfds, NULL, NULL, &timeout);

        if (activity == 0) {
            // Timeout occurred, resend message
            printf("Timeout occurred, resending message...\n");
            continue;
        } else if (activity > 0 && FD_ISSET(sock, &readfds)) {
            // Read acknowledgment from server
            valread = read(sock, buffer, MAX_BUFFER_SIZE);
            if (valread > 0 && strcmp(buffer, ack) == 0) {
                printf("Acknowledgment received from server\n");

                // Now read the server's response
                valread = read(sock, buffer, MAX_BUFFER_SIZE);
                if (valread > 0) {
                    printf("Server: %s\n", buffer);
                    break; // Exit the loop after receiving response
                }
            }
        } else {
            printf("Error in receiving acknowledgment\n");
        }
    }

    return 0;
}
