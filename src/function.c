#include "function.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("shell");
        }
    }
    return 1;
}

int shell_help(char **args) {
    printf("Basic-Shell help:\n");
    for (int i = 0; i < shell_num_builtins(); i++) {
        printf("%s\n", builtin_str[i]);
    }
    return 1;
}

int shell_exit(char **args) {
    return 0;
}

// return number of builtins
int shell_num_builtins(void) {
    return sizeof(builtin_str) / sizeof(char *);
}

