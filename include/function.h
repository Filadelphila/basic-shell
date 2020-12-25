#ifndef FUNCTION
#define FUNCTION

#include <stdlib.h>

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

int shell_num_builtins(void);

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

#endif
