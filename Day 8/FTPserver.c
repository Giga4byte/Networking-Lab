#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main () {
  struct sockaddr_in serveraddr, clientaddr;
  int serversock, newserversock, n, f;
  char filename[100], filedata[300];
  socklen_t clientsize;

  // SOCKET creation
  serversock = socket(AF_INET, SOCK_STREAM, 0);
  if (serversock < 0) {
    perror("socket");
    return 1;
  }

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddr.sin_port = htons(8080);

  // BIND socket
  if(bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
    perror("bind");
    return 1;
  }

  // LISTEN
  if(listen(serversock, 5) == -1) {
    perror("listen");
    return 1;
  }

  printf ("Server listening on port 8080...");

  while (1) {
    clientsize = sizeof(clientaddr);
    
    newserversock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
    if (newserversocket < 0) {
      perror ("accept");
      return 1;
    } 
    printf ("Client connected!");
    
    n = read(newserversock, filename, sizeof(filename)-1);
    if (n <= 0) {
      perror ("file name read");
      close(newserversock);
      continue;
    }
    filename[n] = '\0';
    printf("Requested file: %s\n", filename);

    f = open(filename, O_RDONLY);
    if (f == -1) {
      perror("open");
      write(newserversock, "File not found", 14);
      close(newserversock);
      continue;
    }

    n = read(f, filedata, sizeof(filedata)-1);
    if (n > 0) {
      filedata[n] = '\0';
      printf("File contents: %s\n", filedata);
      write(newserversock, filedata, n);
    } else {
      perror("read");
    }

    close(f);
    close(newserversock);
  }
  close(serversock);
  return 0;
}
