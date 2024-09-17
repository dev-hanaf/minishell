# Minishell

Minishell is a simple Unix shell implementation, designed to provide basic command-line functionality.

## Features

- Command execution
- Built-in commands (cd, echo, pwd, exit,env,export)
- Environment variable expansion
- Input/output redirection
- Pipes
- Signal handling (Ctrl+C, Ctrl+D ,Ctrl+\)

## Building

To build the minishell, run:

```
make
```

## Usage

After building, run the minishell:

```
./minishell
```

## Implemented Built-ins

- `cd`: Change directory
- `echo`: Display a line of text
- `pwd`: Print working directory
- `exit`: Exit the shell
- `env` : list environment variables
- `export` : export enviroment variables

## Notes

- This shell is a simplified version and may not include all features of a full-fledged shell.
