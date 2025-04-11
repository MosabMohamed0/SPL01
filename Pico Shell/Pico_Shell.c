#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#define SIZE 1000000

int main()
{
  char input[SIZE];

  while (1)
  {
    printf("pico shell -> ");
    fflush(stdout);

    if (fgets(input, SIZE, stdin) == NULL)
    {
      break;
    }

    input[strcspn(input, "\n")] = '\0';

    if (*input == '\0')
    {
      continue;
    }

    if (strncmp(input, "echo ", 5) == 0)
    {
      char *text = input + 5;
      char *dst = text;
      int space_flag = 0;

      while (isspace(*text))
        text++;

      while (*text)
      {
        if (isspace(*text))
        {
          if (!space_flag)
          {
            *dst++ = ' ';
            space_flag = 1;
          }
          text++;
        }
        else
        {
          *dst++ = *text++;
          space_flag = 0;
        }
      }
      *dst = '\0';
      printf("%s\n", input + 5);
    }
    else if (strcmp(input, "exit") == 0)
    {
      printf("Good Bye\n");
      break;
    }
    else if (strncmp(input, "cd ", 3) == 0)
    {
      char *directory = input + 3;
      if (chdir(directory) == -1)
      {
        perror("cd error");
      }
    }
    else if (strcmp(input, "pwd") == 0)
    {
      char cwd[SIZE];
      if (getcwd(cwd, sizeof(cwd)) != NULL)
      {
        printf("%s\n", cwd);
      }
      else
      {
        perror("getcwd error");
      }
    }
    else
    {
      pid_t pid = fork();

      if (pid == -1)
      {
        perror("Fork failed");
        continue;
      }
      else if (pid == 0)
      {
        char *args[SIZE / 2];
        char *token = strtok(input, " ");
        int index = 0;

        while (token != NULL)
        {
          args[index++] = token;
          token = strtok(NULL, " ");
        }
        args[index] = NULL;

        if (execvp(args[0], args) == -1)
        {
          perror("Command execution failed");
          exit(EXIT_FAILURE);
        }
      }

      int status;
      if (waitpid(pid, &status, 0) == -1)
      {
        perror("waitpid error");
      }
    }
  }
  return 0;
}