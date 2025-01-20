#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid;
  char cwd[1024];
  pid = fork();
  if (pid < 0) { // pid < 0 means fork() has failed
    perror("Error in creating a new process");
    exit(1);
  }
  if (pid == 0) { // child process
    printf("CHILD PROCESS:\n");
    printf(" My PID is: %d\n", getpid());
    printf(" My Parent's PID is: %d\n", getppid());
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf(" Current working directory: %s\n", cwd);
    } else {
      perror("Error getting current working directory");
      exit(0);
    }
  } else { // parent process
    printf("PARENT PROCESS:\n");
    printf(" My PID is: %d\n", getpid());
    printf(" My Child's PID is: %d\n", pid);
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf(" Current working directory: %s\n", cwd);
    } else {
      perror("Error getting current working directory");
      exit(0);
    }
  }
  return 0;
}
