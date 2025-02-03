// stop and wait arq - server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8082
#define MAX_BUFFER_SIZE 1024

int main() {
	int server_fd, new_socket , i=0;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[MAX_BUFFER_SIZE] = {0};
	char response[MAX_BUFFER_SIZE];
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	} 
	
	// Forcefully attaching socket to the port 8082
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	// Forcefully attaching socket to the port 8082
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	
	while (1) { 
		memset(buffer, 0, sizeof(buffer));
		memset(response, 0, sizeof(response));

		int valread = read(new_socket, buffer, sizeof(buffer) - 1);
		if (valread > 0) {
		    buffer[valread] = '\0'; 
		    //printf("Client: %s\n", buffer);
		}
		if (strcmp(buffer, "....giving up....") == 0) {
			printf("....LOST 1 FRAME....\n");
		}

		printf("Server: ");
		fgets(response, sizeof(response), stdin);
		response[strcspn(response, "\n")] = 0;

		if (strcmp(response, "exit") == 0) {
		    printf("Exiting server...\n");
		    return 0;
		}
		if (strcmp(response, "ACK") == 0) {
			printf("Client has sent this message: %s\n", buffer);
		}

		send(new_socket, response, strlen(response), 0);
		printf("....message has been sent....\n");
	}


	return 0;
}
