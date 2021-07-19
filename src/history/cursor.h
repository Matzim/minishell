#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "vector.h"

/**
** Enum represent specials keys
*/
enum Key
{
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    NEXT_WORD,
    PREV_WORD,
    NEXT_LINE,
    PREV_LINE
};

void move_column(int c, size_t limit, size_t *cur_pos);
void move_on_word(struct vector *vect, int c, size_t *cur_pos);
void del_char(struct vector *vect, int c, size_t *cur_pos);

#endif /* ifndef _CURSOR_H_ */
