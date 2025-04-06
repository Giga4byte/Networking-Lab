#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8091
#define BUFFER_SIZE 1024

int main() {
    int client_socket, windowsize, base=0, count=0, total packets, limit, packnum=0;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE], ack[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("\nEnter the sender's sliding window size : ");
    scanf("%d", &windowsize);
    printf("\nEnter total number of packets to be sent : ");
    scanf("%d", &totalpackets);

    limit = (totalpackets < windowsize) ? totalpackets : windowsize;
    packnum = 0;

    for (int i=0; i<limit; i++) {
        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "%d", i);
        send(client_socket, buffer, strlen(buffer), 0);
        printf("\nClient : sent packet %d, seqnum %d\n", packnum, i);
        packnum++;
        sleep(1);
    }

    while (count < totalpackets) {
        recv(client_socket, buffer, BUFFER_SIZE, 0);
        printf("\n\nServer : sent ack for seqnum %s", buffer);
        sprintf(ack, "%d", base);
        if (strcmp(buffer, ack) == 0) {
            printf("\n\nACK received for seqnum %d", base);
            base = (base+1) % windowsize;
            count++;
        } else {
            printf("\n\nAck not recieved for seqnum %d", base);
            printf("\n\nRetransmitting packets from %d", count);
            limit = ((totalpackets-count) < windowsize) ? (totalpackets-count) : windowsize;
            packnum = count;
            for (int i = 0; i<limit; i++) {
                memset(buffer, 0, BUFFER_SIZE);
                sprintf(buffer, "%d", i);
                send(client_socket, buffer, strlen(buffer), 0);
                printf("\nClient : sent packet %d, seqnum %d", packnum, i);
                packnum++;
                sleep(1);
            }
            base = 0;
        }
    }

    if (count == totalpackets) {
        printf("\nAll packets sent and recieved succesfully.\n");
    }

    strcpy(buffer, "done");
    send(client_socket, buffer, strlen(buffer), 0);
    close(client_socket);
    return 0;
}
