# Nano Shell

A simple Unix-like shell implementation in C with basic shell functionalities.

## Features

- **Command Execution**: Executes basic shell commands like `ls`, `cat`, etc.
- **Built-in Commands**:
  - `cd <directory>`: Change directory
  - `pwd`: Print working directory
  - `exit`: Exit the shell
  - `echo <text>`: Print text to stdout
  - `echo $VAR`: Print environment or shell variable
  - `export VAR=value`: Set environment variables
  - `printenv`: Print all environment variables
- **Variable Support**: Supports shell variables (e.g., `VAR=value`)
- **Environment Variables**: Can access and modify environment variables

## Usage

1. Compile the shell:
   ```bash
   gcc -o Nano_Shell Nano_Shell.c

2. Run the shell:
   ```bash
   ./Nano_Shell
3. Use the shell commands:
   ```bash
   nano shell -> echo Hello World
   Hello World
   nano shell -> VAR=value
   nano shell -> echo $VAR
   value
   
   nano shell -> export PATH=/new/path
   nano shell -> printenv
   ...

   nano shell -> exit
   Good Bye

## Implementation Details

- Uses fork() and execvp() for command execution

- Implements built-in commands directly in C

- Maintains a separate array for shell variables

- Uses standard C library functions for file and process operations

- Includes basic error handling

## Limitations
- Limited to 10 shell variables (MAX_VARS)

- Variable names and values can't contain spaces

- No advanced shell features like pipes, redirections, or scripting

- Simple command parsing (no quoting support)


