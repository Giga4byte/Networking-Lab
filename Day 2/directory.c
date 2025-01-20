#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
struct dirent *dptr;

int main() {
  printf ("Giribala Arun\nS6 CSB\n");
  DIR *dirp;
  // current working directory (".")
  if ((dirp = opendir(".")) == NULL) {
    printf("Failed to open current directory\n");
    exit(1);
  }
  // display contents of the directory
  while ((dptr = readdir(dirp)) != NULL) {
    printf("%s\n", dptr->d_name);
  }
  closedir(dirp);
  return 0;
}
