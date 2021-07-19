#ifndef _SHELL_MANAGEMENT_H_
#define _SHELL_MANAGEMENT_H_

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "../history/history.h"
#include "../history/vector.h"
#include "../libft/libft.h"
#include "manage_input.h"
#include "process.h"

int setup_shell(struct termios origin, char **environ);

#endif /* ifndef _SHELL_MANAGEMENT_H_ */
