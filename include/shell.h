#ifndef SHELL
#define SHELL

#ifndef SHELL_VERSION
    #define SHELL_VERSION "0.0.1"
#endif
#ifndef SHELL_NAME
    #define SHELL_NAME "Basic Shell"
#endif

char *shell_read_line(void);
char **shell_split_line(char *line);
int shell_launch(char **args);
int shell_execute(char **args);
void shell_loop();

#endif
