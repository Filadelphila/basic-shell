#include "shell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "function.h"

char *shell_read_line(void) {
    char *line = NULL;
    ssize_t buffer_size = 0;

    if (getline(&line, &buffer_size, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        }
        else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    line[strlen(line) -1] = '\0';
    return line;
}

char **shell_split_line(char *line) {
    int buffer_size = 64, position = 0;
    char **tokens = malloc(buffer_size * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position++] = token;
        if (position >= buffer_size) {
            buffer_size += 64;
            tokens = realloc(tokens, buffer_size * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "shell, allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

int shell_launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("shell");
    }
    else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int shell_execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }
    for (int i = 0; i < shell_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i]) (args);
        }
    }
    return shell_launch(args);
}

void shell_loop() {
    int status;
    do {
        char *cwd = getcwd(NULL, 0);
        printf("[%s]%s> ", getenv("USER"), cwd);
        char *line = shell_read_line();
        char **args = shell_split_line(line);
        status = shell_execute(args);
    } while(status);
}
