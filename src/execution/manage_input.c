#include "manage_input.h"

#include <stdio.h>

/**
** Write the string on the stdout
** @param str String
** @param len Length of the string
*/
void write_str(char *str, unsigned long long len)
{
    ssize_t offset = 0;

    while (len > 0)
    {
        ssize_t len_write = write(STDOUT_FILENO, str + offset, len);
        offset += len_write;
        len -= len_write;
    }
}

/**
** Return the key enter by the user
*/
int get_user_key(void)
{
    int nread = 0;
    char buf[5] = { 0 };

    while ((nread = read(STDIN_FILENO, &buf[0], 1)) != 1)
    {
        if (nread == -1)
        {
            ft_putstr("get_user_input: read\n");
            exit(1);
        }
    }
    if (buf[0] == '\x1b')
    {
        if (read(STDIN_FILENO, &buf, 5) <= 0)
            return '\x1b';
        if (buf[0] == '[')
        {
            if (buf[1] >= '0' && buf[1] <= '9')
            {
                if (buf[2] == '~')
                {
                    switch (buf[1])
                    {
                    case '3':
                        return DEL_KEY;
                    case '7':
                        return HOME_KEY;
                    case '8':
                        return END_KEY;
                    }
                }
                else if (buf[1] == '1' && buf[2] == ';' && buf[3] == '5')
                {
                    switch (buf[4])
                    {
                    case 'A':
                        return PREV_LINE;
                    case 'B':
                        return NEXT_LINE;
                    case 'C':
                        return NEXT_WORD;
                    case 'D':
                        return PREV_WORD;
                    }
                }
            }
            else
            {
                switch (buf[1])
                {
                case 'A':
                    return ARROW_UP;
                case 'B':
                    return ARROW_DOWN;
                case 'C':
                    return ARROW_RIGHT;
                case 'D':
                    return ARROW_LEFT;
                case 'H':
                    return HOME_KEY;
                case 'F':
                    return END_KEY;
                }
            }
        }
        else if (buf[0] == 'O')
        {
            switch (buf[1])
            {
            case 'H':
                return HOME_KEY;
            case 'F':
                return END_KEY;
            }
        }
        return '\x1b';
    }
    return buf[0];
}

void move_row(int c, size_t size, size_t nb_cols, size_t *cur_pos,
              size_t len_path)
{
    size_t cur_row = (*cur_pos + PROMPT_SIZE + len_path) / nb_cols;

    if (NEXT_LINE == c)
    {
        if ((size - 1 + PROMPT_SIZE + len_path) / nb_cols > cur_row)
        {
            *cur_pos += nb_cols;
            if (*cur_pos > size)
            {
                *cur_pos = size;
            }
        }
    }
    else
    {
        if (cur_row)
        {
            if (*cur_pos < nb_cols)
                *cur_pos = 0;
            else
                *cur_pos -= nb_cols;
        }
    }
}

// Update the display
void write_line(struct vector *vect, size_t cur_pos, int nb_cols, size_t len,
                char *path)
{
    // Modify the screen update with the signal SIGWINCH
    int len_path = ft_strlen(path);
    int max_row = (vect->size - 1 + PROMPT_SIZE + len_path) / nb_cols;
    int nb_col_lines = (cur_pos + PROMPT_SIZE + len_path) / nb_cols;
    char *caps = tigetstr("rc");

    write_str(caps, ft_strlen(caps));
    // Clear current lines
    if (len)
    {
        caps = tiparm(tigetstr("dl"),
                      1 + (int)(len + PROMPT_SIZE + len_path) / nb_cols);
    }
    else
    {
        caps = tiparm(tigetstr("dl"), 1 + max_row);
    }
    write_str(caps, ft_strlen(caps));
    // Print the new line
    write_str(path, ft_strlen(path));
    write_str(PROMPT, PROMPT_SIZE);
    write_str(vect->data, vect->size);
    // Put the cursor at the good place
    if (max_row)
    {
        caps = tiparm(tigetstr("cuu"), max_row);
        write_str(caps, ft_strlen(caps));
    }
    caps = tiparm(tigetstr("hpa"), 0);
    write_str(caps, ft_strlen(caps));
    caps = tigetstr("sc");
    write_str(caps, ft_strlen(caps));
    if (nb_col_lines)
    {
        caps = tiparm(tigetstr("cud"), nb_col_lines);
        write_str(caps, ft_strlen(caps));
    }
    caps =
        tiparm(tigetstr("hpa"), (cur_pos + PROMPT_SIZE + len_path) % nb_cols);
    write_str(caps, ft_strlen(caps));
}

// Need to manage historic and all key
char *get_user_line(struct vector *vect, struct s_history *hist, char **env)
{
    size_t cur_pos = 0;
    int key = 0;

    // Modify the update function
    int nb_cols = tigetnum("cols");
    char *save = tigetstr("sc");

    if (nb_cols == -2 || nb_cols == -1)
        return NULL;
    write_str(save, ft_strlen(save));
    char *path = get_value(env, "PWD");
    write_str(path, ft_strlen(path));
    write_str(PROMPT, PROMPT_SIZE);
    while (key != '\r')
    {
        size_t len = 0;
        // Get the user key
        key = get_user_key();
        if (key == ARROW_RIGHT || key == ARROW_LEFT || key == END_KEY
            || key == HOME_KEY)
        {
            move_column(key, vect->size, &cur_pos);
        }
        else if (key == ARROW_UP || key == ARROW_DOWN)
        {
            len = vect->size;
            vector_push(vect, '\0');
            cur_pos = get_from_hist(hist, vect, key);
        }
        else if (key == DEL_KEY || key == BACKSPACE)
        {
            del_char(vect, key, &cur_pos);
        }
        else if (key == NEXT_LINE || key == PREV_LINE)
        {
            move_row(key, vect->size, nb_cols, &cur_pos, ft_strlen(path));
        }
        else if (key == NEXT_WORD || key == PREV_WORD)
        {
            move_on_word(vect, key, &cur_pos);
        }
        else if ((char)key > 31)
        {
            vector_insert(vect, cur_pos++, key);
        }
        else if (key == '\r')
        {
            vector_push(vect, '\0');
            put_history(hist, vect->data);
        }
        write_line(vect, cur_pos, nb_cols, len, path);
    }
    free(path);
    return vect->data;
}
