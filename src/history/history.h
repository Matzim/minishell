#ifndef _HISTORY_H_
#define _HISTORY_H_
#include <stdlib.h>

#include "../libft/libft.h"
#include "cursor.h"
#include "vector.h"

#define MAX_HISTORY 10

/**
** Structure that represent the history of the shell
*/
struct s_history
{
    size_t current_line; /**< size_t current_line Current selection in the
                            history */
    size_t search_pos; /**< size_t search_pos  */
    size_t max_capacity; /**< size_t max_capacity Capacity of history  */
    char *keep_line; /**< char* keep_line Save the last selected line */
    char **data; /**< char** data Array that save all data */
};

struct s_history *init_history(size_t max);
void put_history(struct s_history *hist, char *line);
size_t get_from_hist(struct s_history *hist, struct vector *vect, int pos);
void free_history(struct s_history *hist);

#endif /* ifndef _HISTORY_H_ */
