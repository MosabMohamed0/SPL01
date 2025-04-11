# Micro Shell

## Overview
The "Micro Shell" is a simple Unix-like shell implementation in C that supports environment variable management, basic command execution, input/output redirection, and more. It is designed to mimic the functionality of a basic shell with features such as variable assignment, `echo`, `cd`, `pwd`, `exit`, and file redirection.

## Features

- **Variable Assignment**: Supports defining variables in the format `VAR=value`.
- **Echo**: Supports printing environment variables and text to the terminal.
- **Change Directory (`cd`)**: Changes the current working directory.
- **Print Working Directory (`pwd`)**: Displays the current working directory.
- **Export Environment Variables (`export VAR=value`)**: Sets environment variables for the shell session.
- **Print Environment (`printenv`)**: Displays all environment variables.
- **Input/Output Redirection**: Supports redirection for standard input (`<`), standard output (`>` and `>>`), and standard error (`2>`).
- **Command Execution**: Executes external commands using `fork()` and `execvp()`.

## Usage

### Basic Commands
- `echo $VAR`: Prints the value of the environment variable `VAR`.
- `echo [text]`: Prints the given text to the terminal.
- `cd [directory]`: Changes the current directory to `directory`.
- `pwd`: Prints the current working directory.
- `exit`: Exits the shell.
- `export VAR=value`: Sets an environment variable `VAR` with a specified `value`.
- `printenv`: Prints all environment variables.

### Redirection
- `< file`: Redirects input from `file`.
- `> file`: Redirects output to `file`, overwriting the content.
- `>> file`: Redirects output to `file`, appending to the content.
- `2> file`: Redirects standard error to `file`.

## Compilation

1. Compile the program:

    ```bash
    gcc -o Micro_Shell Micro_Shell.c

2. Running the Shell
    ```bash
    ./Micro_Shell

## Limitations

- It supports only basic shell commands.
- Limited error handling.
- No support for complex pipelines or background processes.
- Environment variables are limited to a fixed number (MAX_VARS).
