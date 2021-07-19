#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../libft/libft.h"
#include "builtins.h"
#include "get_environ.h"

#define NB_BUILTINS 6

void free_tab(char **tabu);
int execute_line(char **argv, char **envp, int *stop);

#endif /* ifndef _PROCESS_H_ */
