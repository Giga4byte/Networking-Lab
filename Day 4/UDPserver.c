#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
	// Initialise server_fd, bind_status, serv_addr, client_addr, client_addr_len
	int server_fd, bind_status;
	struct sockaddr_in serv_addr, client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char buffer[MAX_BUFFER_SIZE];

	// Check server_fd
	server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_fd < 0) {
		printf("\terror...\n");
		exit(EXIT_FAILURE);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	// Check bind_status
	bind_status = bind (server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (bind_status < 0) {
		printf("\terror...\n");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	
	while(1) {
		memset(buffer, 0, MAX_BUFFER_SIZE); // clear buffer
		ssize_t bytes_received = recvfrom(server_fd, buffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_addr, &client_addr_len);
		if(bytes_received < 0) {
			printf ("\treceive failed...\n");
			break;
		}
		
		buffer[bytes_received] = '\0';
		printf ("Client: %s\n", buffer);
		
		if (strcmp(buffer, "exit") == 0) {
			printf("Messages have ended\n");
			break;
		}
		
		printf("Server: ");
		fgets(buffer, MAX_BUFFER_SIZE, stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		ssize_t bytes_sent = sendto(server_fd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&client_addr, client_addr_len);
		if(bytes_sent < 0) {
			printf("\tsend error...\n");
			break;
		}
		
		if(strcmp(buffer, "exit") == 0) {
			printf("Messages have ended\n");
			break;
		}
	}
	close(server_fd);
	return 0;
}
