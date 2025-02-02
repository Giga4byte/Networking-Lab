#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_ADDRESS "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
	int client_socket;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	socklen_t server_addr_len =sizeof(server_addr);
	client_socket = socket(AF_INET,SOCK_DGRAM, 0);

	if (client_socket < 0) {
		printf("\terror...\n");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, SERVER_ADDRESS, &server_addr.sin_addr) <= 0) {
		printf("\tinvalid address...\n");
		close(client_socket);
		exit(EXIT_FAILURE);
	}
	while (1) {
		printf("Client: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		
		buffer[strcspn(buffer, "\n")] = '\0';
		ssize_t bytes_sent = sendto(client_socket, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&server_addr, server_addr_len);
		if (bytes_sent < 0) {
			printf("\terror...\n");
			break;
		}
		if (strcmp(buffer, "exit") == 0) {
			printf("Messages have ended\n");
			break;
		}
		memset(buffer, 0, BUFFER_SIZE);
		ssize_t bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &server_addr_len);
		if (bytes_received < 0) {
			printf("\terror...\n");
			break;
		}
		buffer[bytes_received] = '\0';
		printf("Server: %s\n", buffer);
		if (strcmp(buffer, "exit") == 0) {
			printf("Messages have ended\n");
			break;
		}
	}
	close(client_socket);
	return 0;
