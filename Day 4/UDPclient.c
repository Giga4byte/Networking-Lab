// CLIENT SIDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_ADDRESS "127.0.0.1"

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char message[1024];  // Initialize a buffer to store the client input

    // Prompt the user to enter the message
    printf("Enter the message to send: ");
    scanf("%[^\n]", message);  // Read the entire line, including spaces

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_ADDRESS, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }

    // Send the message to the server
    sendto(sock, (const char *)message, strlen(message), 0, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Message sent to server: %s\n", message);

    // Receive the response from the server
    int n;
    socklen_t len = sizeof(serv_addr);
    n = recvfrom(sock, (char *)buffer, 1024, 0, (struct sockaddr *)&serv_addr, &len);
    buffer[n] = '\0';  // Null-terminate the received data
    printf("Server response: %s\n", buffer);

    return 0;
}
