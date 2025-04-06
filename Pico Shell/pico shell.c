#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char input[1000000];

  while (1)
  {

    printf("Pico shell -> ");

    if (fgets(input, 1000000, stdin) == NULL)
      break;

    input[strlen(input) - 1] = '\0';

    if (strlen(input) == 0)
      continue;
    if (strncmp(input, "echo ", 5) == 0)
      printf("%s\n", input + 5);
    else if (strcmp(input, "exit") == 0)
    {
      printf("Good Bye\n");
      break;
    }
    else if (strcmp(input, "pwd") == 0)
    {
      char *mylocation = getcwd(NULL, 0);

      if (mylocation == NULL)
      {
        printf("pwd error");
        exit(-1);
      }
      printf("%s\n", mylocation);
    }
    else if (strncmp(input, "cd ", 3) == 0)
    {
      char *path = input + 3;
      if (chdir(path) == 0)
        printf("success\n");
      else
        printf("Can't change directory\n");
    }
    else
      printf("Invalid command\n");
  }
  return 0;
}
