#include "cursor.h"

/**
** Manage the cursor position.
**
** @param key Key pressed by user
** @param max_col Number columns of the line
** @param cur_pos Position of the cursor
*/
void move_column(int key, size_t max_col, size_t *cur_pos)
{
    if (key == ARROW_LEFT)
    {
        if (*cur_pos > 0)
        {
            *cur_pos = *cur_pos - 1;
        }
    }
    else if (key == HOME_KEY)
    {
        *cur_pos = 0;
    }
    else if (key == END_KEY)
    {
        *cur_pos = max_col;
    }
    else
    {
        if (*cur_pos < max_col)
        {
            *cur_pos = *cur_pos + 1;
        }
    }
}

/**
** Manage the position of the cursor to move forward or backward word by word.
** @param vect Content of the line
** @param key Key pressed by user
** @param cur_pos Position of the cursor
*/
void move_on_word(struct vector *vect, int key, size_t *cur_pos)
{
    size_t pos = *cur_pos;

    if (key == NEXT_WORD)
    {
        while (pos < vect->size)
        {
            if (vect->data[pos] != ' ')
            {
                if (pos + 1 < vect->size && vect->data[pos + 1] == ' ')
                {
                    pos += 1;
                    break;
                }
            }
            pos++;
        }
    }
    else
    {
        if (pos > 0)
            pos--;
        while (pos > 0)
        {
            if (vect->data[pos] != ' ')
            {
                if (vect->data[pos - 1] == ' ')
                {
                    break;
                }
            }
            pos--;
        }
    }
    *cur_pos = pos;
}

/**
** Delete a character
** @param vect Content of the line
** @param key Key pressed by user
** @param cur_pos Position of the cursor
*/
void del_char(struct vector *vect, int key, size_t *cur_pos)
{
    char _;

    if (key == DEL_KEY)
    {
        if (*cur_pos != vect->size)
        {
            vector_remove(vect, *cur_pos, &_);
        }
    }
    else
    {
        if (*cur_pos != 0)
        {
            vector_remove(vect, *cur_pos - 1, &_);
            *cur_pos = *cur_pos - 1;
        }
    }
}
