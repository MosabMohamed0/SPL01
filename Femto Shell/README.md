# Femto Shell

Femto Shell is a simple command-line interface written in C. It's a minimal shell that supports a couple of basic commands to demonstrate input handling and string manipulation.

## Features

- `echo [text]`: Prints the text after the `echo` keyword.
- `exit`: Exits the shell with a goodbye message.
- Handles invalid or unknown commands gracefully.
- Ignores empty inputs.

## Example

```bash
 Femto shell -> echo Hello, World!
 Hello, World!
 Femto shell -> unknowncommand
 Invalid command
 Femto shell -> exit
 Good Bye
```

## Building

To compile the program:

```bash
gcc Femto_Shell.c -o Femto_Shell
```

## Running

```bash
./Femto_Shell
```

## File Structure

- `Femto_Shell.c` – The main source code file for the shell.
- `README.md` – This file.

## Notes

- The program uses a large static buffer (`char input[1000000]`), which is sufficient for most input cases.
- This shell is designed for educational and demonstration purposes.
