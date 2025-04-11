# Pico Shell

Pico Shell is a lightweight command-line shell written in C. It supports a few basic commands and can execute external programs using `fork` and `execvp`.

## Features

- `echo [text]`: Outputs cleaned-up text with normalized spaces.
- `cd [directory]`: Changes the current working directory.
- `pwd`: Prints the current working directory.
- `exit`: Exits the shell with a farewell message.
- Executes valid external commands (like `ls`, `cat`, etc.).
- Handles extra spaces in input commands cleanly.
- Waits for child processes to finish before accepting new input.

## Example

```bash
pico shell -> echo    Hello    Pico   Shell!
Hello Pico Shell!
pico shell -> pwd
/home/user
pico shell -> cd ..
pico shell -> pwd
/home
pico shell -> ls
Documents  Downloads  pico_shell.c
pico shell -> exit
Good Bye
```

## Building

To compile the program:

```bash
gcc Pico_Shell.c -o Pico_Shell
```

## Running

```bash
./Pico_Shell
```

## Notes

- Commands are parsed using `strtok` and passed to `execvp`.
- `echo` behavior includes space normalization (removes extra spaces).
- Large input buffer size defined by `#define SIZE 1000000`.
