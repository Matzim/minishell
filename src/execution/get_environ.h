#ifndef _GET_ENVIRON_H_
#define _GET_ENVIRON_H_

#include <stdlib.h>

void print_env(char **env);
char *check_variable(char *value, char *var);
char *get_value(char *env[], char *var);

#endif /* ifndef _GET_ENVIRON_H_ */
