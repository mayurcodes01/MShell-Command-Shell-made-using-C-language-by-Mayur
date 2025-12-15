# MShell- Minimal Windows Command Line Shell

## Description

MShell is a custom-built command line shell developed in C for the Windows operating system using the Windows API. The project demonstrates how a basic shell works internally, including command parsing, built-in command handling, environment variable management, and external process execution.

Unlike traditional shells, MShell is intentionally lightweight and educational. It focuses on core operating system concepts such as process creation, directory management, and user input handling, making it a strong learning project for system-level programming.

The shell supports both internally implemented commands and standard Windows commands by leveraging the system PATH and the CreateProcess API.

## Key Features

- Interactive command prompt
- Built-in command handling (cd, pwd, echo, cls, etc.)
- Execution of external Windows commands and executables
- Environment variable management
- Command history support
- Native Windows API–based process creation
- Portable executable for easy distribution

## Supported Platforms

- Windows (Windows 7 and later)

## Purpose of the Project

The primary goal of MShell is educational. It helps in understanding:

- How command-line shells work internally
- The difference between built-in and external commands
- Windows process creation and control
- Environment variable handling
- Basic shell architecture and control flow

This project serves as a foundation for building more advanced shell features such as piping, redirection, scripting, and job control.

## Prerequisites

To build MShell from source, MinGW must be installed on the system. MinGW provides the GCC compiler and required toolchain for compiling C programs on Windows.

## Build Instructions

After installing MinGW and adding it to the system PATH, compile MShell using:

```bash
gcc minishell.c -o mshell.exe -static
```

## How to Run

```cmd
mshell.exe
```

## Limitations

- Does not support pipes ( | )
- Does not support input/output redirection
- Does not support background execution
- Limited argument parsing (no quoted strings)

## Future Enhancements

- Pipe and redirection support
- Script execution
- Command auto-completion
- Improved tokenizer with quote handling
- Job control and background tasks

## Author

Developed as a system programming project to explore shell internals and Windows process management.
