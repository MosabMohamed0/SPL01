#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>


#define SIZE 1000000


#define MAX_VARS 10
#define MAX_VAR_LEN 50
#define MAX_VAL_LEN 50

typedef struct
{
  char variable[MAX_VAR_LEN];
  char value[MAX_VAL_LEN];
} Variable;

Variable variables[MAX_VARS];
int var_count = 0;


// Function to validate the format of the input
int
isValidFormat_variables (const char *input)
{
  // Find the position of '=' in the input string
  const char *equals = strchr (input, '=');

  // If '=' is not found, return invalid
  if (equals == NULL)
    {
      return 0;
    }

  // If there's nothing before or after '=', return invalid
  if (equals == input || *(equals + 1) == '\0')
    {
      return 0;
    }

  // Check if the variable part (before '=') contains only valid characters (alphanumeric or '_')
  for (const char *ptr = input; ptr < equals; ptr++)
    {
      if (!isalnum (*ptr) && *ptr != '_')
        {
          return 0;             // Invalid character in variable name
        }
    }

  // Check if the value part (after '=') contains only valid characters (alphanumeric or '_')
  for (const char *ptr = equals + 1; *ptr != '\0'; ptr++)
    {
      if (!isalnum (*ptr) && *ptr != '_')
        {
          return 0;             // Invalid character in value
        }
    }

  // Ensure there are no spaces before or after '='
  if (*(equals - 1) == ' ' || *(equals + 1) == ' ')
    {
      return 0;                 // Space found around '='
    }

  return 1;                     // Valid format
}



int
main ()
{

  char input[SIZE];

  while (1)
    {
      printf ("micro shell -> ");
      fflush (stdout);

      if (fgets (input, SIZE, stdin) == NULL)
        {
          break;
        }

      input[strcspn (input, "\n")] = '\0';

      if (*input == '\0')
        {
          continue;
        }


      if (strncmp (input, "echo $", 6) == 0)
        {
          char *text = input + 6;
          int f = 0;
          for (int i = 0; i < var_count; i++)
            {
              if (strcmp (variables[i].variable, text) == 0)
                {
                  printf ("%s\n", variables[i].value);
                  f = 1;
                }
            }
          if (f == 0)
            {
              // search in env_variables
              char *value = getenv (text);
              if (value)
                {
                  printf ("%s\n", value);
                }
              else
                {
                  printf ("\n");
                }
            }
        }
      else if (strncmp (input, "echo ", 5) == 0)
        {

          char *text = input + 5;
          char *dst = text;
          int space_flag = 0;

          while (isspace (*text))
            text++;

          while (*text)
            {
              if (isspace (*text))
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
          printf ("%s\n", input + 5);

        }
      else if (strcmp (input, "exit") == 0)
        {
          printf ("Good Bye\n");
          break;
        }
      else if (strncmp (input, "cd ", 3) == 0)
        {
          char *directory = input + 3;
          if (chdir (directory) == -1)
            {
              perror ("cd error");
            }
        }
      else if (strcmp (input, "pwd") == 0)
        {
          char cwd[SIZE];
          if (getcwd (cwd, sizeof (cwd)) != NULL)
            {
              printf ("%s\n", cwd);
            }
          else
            {
              perror ("getcwd error");
            }
        }
      else if (isValidFormat_variables (input))
        {
          const char *equals = strchr (input, '=');
          int var_len = equals - input;
          int val_len = strlen (input) - var_len - 1;

          if (var_count < MAX_VARS)
            {
              strncpy (variables[var_count].variable, input, var_len);
              variables[var_count].variable[var_len] = '\0';
              strncpy (variables[var_count].value, equals + 1, val_len);
              variables[var_count].value[val_len] = '\0';
              var_count++;
            }
        }
      else if (strncmp (input, "export ", 7) == 0)
        {
          char *assignment = input + 7;
          char *equal_sign = strchr (assignment, '=');

          if (!equal_sign || equal_sign == assignment
              || *(equal_sign + 1) == '\0')
            {
              printf ("Invalid format. Use: export VAR=value\n");
              continue;
            }

          *equal_sign = '\0';
          char *name = assignment;
          char *value = equal_sign + 1;

          if (setenv (name, value, 1) != 0)
            {
              perror ("setenv failed");
            }
        }
      else if (strcmp (input, "printenv") == 0)
        {
          extern char **environ;
          for (char **env = environ; *env != NULL; env++)
            {
              printf ("%s\n", *env);
            }
        }
      else
        {


          // Handle I/O redirection
          char *input_file = NULL;
          char *output_file = NULL;
          char *stderr_file = NULL;
          int append = 0;

          // Check for input redirection ('<')
          char *input_redirect = strchr (input, '<');
          if (input_redirect != NULL)
            {
              *input_redirect = '\0';   // Split the command
              input_file = strtok (input_redirect + 1, " \t");
            }


          char *output_redirect = strchr (input, '>');
          if (output_redirect != NULL && *(output_redirect - 1) != '2')
            {                   // Ensure it's not '2>'
              if (*(output_redirect + 1) == '>')
                {               // Check for '>>'
                  append = 1;
                  *output_redirect = '\0';
                  output_file = strtok (output_redirect + 2, " \t");
                }
              else
                {
                  *output_redirect = '\0';
                  output_file = strtok (output_redirect + 1, " \t");
                }
            }


          char *stderr_redirect = strstr (input, "2>");
          if (stderr_redirect != NULL)
            {
              *stderr_redirect = '\0';
              stderr_file = strtok (stderr_redirect + 2, " \t");
            }





          pid_t pid = fork ();

          if (pid == -1)
            {
              perror ("Fork failed");
              continue;
            }
          else if (pid == 0)
            {


              // Handle input redirection
              if (input_file != NULL)
                {
                  int fd = open (input_file, O_RDONLY);
                  if (fd == -1)
                    {
                      printf ("open input file");
                      exit (EXIT_FAILURE);
                    }
                  dup2 (fd, STDIN_FILENO);
                  close (fd);
                }

              // Handle output redirection
              if (output_file != NULL)
                {
                  int fd;
                  if (append)
                    {
                      fd =
                        open (output_file, O_WRONLY | O_CREAT | O_APPEND,
                              0644);
                    }
                  else
                    {
                      fd =
                        open (output_file, O_WRONLY | O_CREAT | O_TRUNC,
                              0644);
                    }
                  if (fd == -1)
                    {
                      printf ("open output file\n");
                      exit (EXIT_FAILURE);
                    }
                  dup2 (fd, STDOUT_FILENO);
                  close (fd);
                }

              // Handle stderr redirection
              if (stderr_file != NULL)
                {
                  int fd =
                    open (stderr_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                  if (fd == -1)
                    {
                      printf ("open stderr file\n");
                      exit (EXIT_FAILURE);
                    }
                  dup2 (fd, STDERR_FILENO);
                  close (fd);
                }



              char *args[SIZE / 2];
              char *token = strtok (input, " ");
              int index = 0;

              while (token != NULL)
                {
                  args[index++] = token;
                  token = strtok (NULL, " ");
                }
              args[index] = NULL;

              if (execvp (args[0], args) == -1)
                {
                  perror ("Command execution failed");
                  exit (EXIT_FAILURE);
                }
            }

          int status;
          if (waitpid (pid, &status, 0) == -1)
            {
              perror ("waitpid error");
            }
        }
    }
  return 0;
}
