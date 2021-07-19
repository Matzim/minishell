#ifndef _MANAGE_INPUT_H_
#define _MANAGE_INPUT_H_

#include <curses.h>
#include <term.h>

#include "../history/cursor.h"
#include "../history/history.h"
#include "../history/vector.h"
#include "../libft/libft.h"
#include "get_environ.h"

#define PROMPT ">$ "
#define PROMPT_SIZE 3

void write_str(char *str, unsigned long long len);
int get_user_key(void);
char *get_user_line(struct vector *vect, struct s_history *hist, char **env);

#endif /* ifndef _MANAGE_INPUT_H_ */
