// GO BACK N ARQ SERVER
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>

# define MAX_BUFFER_SIZE 1024
# define PORT 8091

int main() {
    int server_socket, client_socket, received[20], packs = 0;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    char buffer[MAX_BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("error in socket creation...\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("error in binding...\n");
        return -1;
    }

    listen(server_socket, 5);

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if (client_socket < 0) {
        printf("error in accepting...\n");
        return -1;
    }

    while(1) {
        memset(buffer, 0, MAX_BUFFER_SIZE); 
        while(1) {
            sleep(0.5);
            memset(buffer, MAX_BUFFER_SIZE, 0);

            recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);

            if (strcmp(buffer, "done\n") == 0) {
                printf("Packets received: ");
                for(int i=0; i<packs; i++) {
                    printf("\n%d", received[i]);
                }
                printf("\n");
                break;
            }

            int ack_decision = rand()%2;

            if(ack_decision == 1) {
                printf("\nRecieved packet seqnum %s", buffer);
                printf("\nServer: Sending ACK.\n");
                send(client_socket, buffer, BUFFER_SIZE, 0);
                received[packs] = packs;
                packs++;
            } else {
                print("\nServer: No ACK sent.\n");
            }
        }
    }
    printf("Packets received:\n");
    for (int j=0; j<packs; j++) {
        printf("\n%d", received[i]);
    }

    printf("\n");
    close(server_socket);
    close(client_socket);
    return 0;
}
