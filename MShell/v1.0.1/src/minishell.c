
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_ARGS 64
#define HISTORY_SIZE 50

char history[HISTORY_SIZE][MAX_LINE];
int history_count = 0;

void add_history(const char* cmd) {
    if (history_count < HISTORY_SIZE) {
        strcpy(history[history_count++], cmd);
    }
}

void show_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d  %s\n", i + 1, history[i]);
    }
}

void parse_line(char* line, char** args) {
    int i = 0;
    char* token = strtok(line, " ");

    while (token && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}


int cmd_cd(char** args) {
    if (!args[1]) {
        printf("cd: missing argument\n");
        return 1;
    }
    if (!SetCurrentDirectory(args[1])) {
        printf("cd: directory not found\n");
    }
    return 1;
}

int cmd_pwd() {
    char buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    printf("%s\n", buffer);
    return 1;
}

int cmd_cls() {
    system("cls");
    return 1;
}

int cmd_echo(char** args) {
    for (int i = 1; args[i]; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 1;
}

int cmd_set(char** args) {
    if (!args[1] || !args[2]) {
        printf("Usage: set VAR VALUE\n");
        return 1;
    }
    SetEnvironmentVariable(args[1], args[2]);
    return 1;
}

int cmd_get(char** args) {
    if (!args[1]) {
        printf("Usage: get VAR\n");
        return 1;
    }

    char buffer[512];
    if (GetEnvironmentVariable(args[1], buffer, 512)) {
        printf("%s\n", buffer);
    }
    else {
        printf("Variable not found\n");
    }
    return 1;
}

int cmd_help() {
    printf(
        "MShell Commands:\n"
        "cd <dir>       Change directory\n"
        "pwd            Show current directory\n"
        "cls            Clear screen\n"
        "echo <text>    Print text\n"
        "set VAR VAL    Set environment variable\n"
        "get VAR        Get environment variable\n"
        "history        Show command history\n"
        "exit           Exit shell\n"
    );
    return 1;
}


int handle_builtin(char** args) {
    if (strcmp(args[0], "cd") == 0) return cmd_cd(args);
    if (strcmp(args[0], "pwd") == 0) return cmd_pwd();
    if (strcmp(args[0], "cls") == 0) return cmd_cls();
    if (strcmp(args[0], "echo") == 0) return cmd_echo(args);
    if (strcmp(args[0], "set") == 0) return cmd_set(args);
    if (strcmp(args[0], "get") == 0) return cmd_get(args);
    if (strcmp(args[0], "help") == 0) return cmd_help();
    if (strcmp(args[0], "history") == 0) {
        show_history();
        return 1;
    }
    if (strcmp(args[0], "exit") == 0) return 0;

    return -1;  // Not a built-in
}


void execute_external(char* line) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    if (!CreateProcess(
        NULL,
        line,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        printf("Command not found\n");
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


int main() {
    char line[MAX_LINE];
    char line_copy[MAX_LINE];
    char* args[MAX_ARGS];

    while (1) {
        printf("MShell> ");
        fflush(stdout);

        if (!fgets(line, MAX_LINE, stdin))
            break;

        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        strcpy(line_copy, line);
        add_history(line);

        parse_line(line, args);

        int status = handle_builtin(args);
        if (status == 0) break;
        if (status == -1) {
            execute_external(line_copy);
        }
    }

    return 0;
}


