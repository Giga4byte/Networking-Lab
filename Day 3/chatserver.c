#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()

#define PORT 8080 


void chat(int connfd) { 
    char string[50]; 
    int n, i=1;
    while (i < 10) { 
        read(connfd, string, sizeof(string)); // read the message from client and copy it in string
        printf("  From Alice: %s  To Alice: ", string); // print string which contains the client contents 
        bzero(string, 50); 
        n = 0; 
        // copy server message in the buffer 
        while ((string[n++] = getchar()) != '\n'); 
        // and send that buffer to client 
        write(connfd, string, sizeof(string)); 
  
        // if msg contains "Exit" then server exit and chat ended
        if (strncmp("exit", string, 4) == 0) { 
            printf("server exit...\n"); 
            break;
        } 
        i++;
    } 
} 
  
  
int main() { 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("Socket bind failed...\n"); 
        exit(0); 
    } 
   
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 

    len = sizeof(cli);   
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (struct sockaddr*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server has accepted the client...\n"); 
  
    // Function for chatting between client and server 
    chat(connfd); 
  
    // After chatting close the socket 
    close(sockfd); 
}
