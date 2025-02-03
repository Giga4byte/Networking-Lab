// stop and wait arq - client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_ADDRESS "127.0.0.1"

int main() {
	int sock = 0, valread, i=0;
	struct sockaddr_in serv_addr;
	char message[1024];
	char buffer[1024] = {0};
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, SERVER_ADDRESS, &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		memset(message, 0, sizeof(message));

		printf("Client: ");
		fgets(message, sizeof(message), stdin);
		message[strcspn(message, "\n")] = 0;

		if (strcmp(message, "exit") == 0) {
		    printf("Exiting client...\n");
		    return 0;
		}

		send(sock, message, strlen(message), 0);
		printf("....message has been sent....\n");

		int valread = read(sock, buffer, sizeof(buffer) - 1);
		if (valread > 0) {
		    buffer[valread] = '\0';
		    printf("Server: %s\n", buffer);
		}
	}

	
	return 0;
}
