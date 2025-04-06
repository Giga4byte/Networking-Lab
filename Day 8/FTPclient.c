#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <fcntl.h> 
 
int main() {
  int clientsock, n, rdret, length; 
  struct sockaddr_in serveraddr;
  char filename[100], filedata[300]; // Fixed declaration 
   
  // Initialize server address 
  memset(&serveraddr, 0, sizeof(serveraddr)); 
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(8080);
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

  clientsock = socket(AF_INET, SOCK_STREAM, 0); 
  if (clientsock == -1) { 
      perror("Socket creation failed"); 
      return 1; 
  } 

  if (connect(clientsock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
    perror("Error: Cannot connect to server"); 
    close(clientsock); 
    return 1; 
  }
  
  // Get filename from user 
  printf("\nEnter the name of the file: "); 
  scanf("%s", filename); 
  length = strlen(filename) + 1; // Include null terminator 
  write(clientsock, filename, length); 
  
  // Read file contents from the server
  rdret = read(clientsock, filedata, sizeof(filedata) - 1); 
  if (rdret > 0) { 
    filedata[rdret] = '\0';  
    printf("\nThe contents of the file:\n\n%s\n", filedata); 
  } else { 
    printf("\nError: Could not read file from server.\n"); 
  } 
  
  close(clientsock); 
  return 0;
}
