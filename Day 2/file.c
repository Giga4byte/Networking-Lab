#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  char input[20], output[20];
  
  printf ("Enter the name of the input file: ");
  scanf (" %s", input);
  printf ("Enter the name of the output file: ");
  scanf (" %s", output);
  
  int src_fd = open(input, O_RDONLY);
  if (src_fd == -1) {
    perror("Error opening source file\n");
    return 1;
  }
  
  int dest_fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (dest_fd == -1) {
    perror("Error opening destination file\n");
    close(src_fd);
    return 1;
  }
  
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read, bytes_written;
  while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
    bytes_written = write(dest_fd, buffer, bytes_read);
    if (bytes_written != bytes_read) {
      perror("Error writing to destination file");
      close(src_fd);
      close(dest_fd);
      return 1;
    }
  }
  
  if (bytes_read == -1) {
    perror("Error reading from source file");
  }
  
  close(src_fd);
  close(dest_fd);
  printf ("File copied!");
  return 0;
}
