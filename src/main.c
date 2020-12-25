#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(int argc, char **argv[]) {
    printf("%s %s\n", SHELL_NAME, SHELL_VERSION);
    shell_loop();
    return EXIT_SUCCESS;
}

