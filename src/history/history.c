#include "history.h"

/**
** Initialise the struct s_history
** @param max Maximum history entries
** @return Structure s_history
*/
struct s_history *init_history(size_t max)
{
    struct s_history *hist = malloc(sizeof(struct s_history));
    size_t index = 0;
    char **data = malloc(sizeof(char *) * (max + 1));

    // Manage errors of malloc function
    if (hist == 0 || data == 0)
    {
        exit(3);
    }
    while (index < max + 1)
    {
        data[index] = NULL;
        index++;
    }
    hist->data = data;
    hist->current_line = 0;
    hist->search_pos = 0;
    hist->keep_line = NULL;
    hist->max_capacity = max + 1;
    return hist;
}

/**
** Save a command in the history
** @param hist Current history of the shell
** @param line Command that needs to be saved
*/
void put_history(struct s_history *hist, char *line)
{
    size_t index = 0;

    while (line[index] != '\0' && line[index] == ' ')
    {
        index++;
    }
    // Check if the line is empty, we don't save empty line
    if (line[index] != '\0')
    {
        if (hist->data[hist->current_line] != NULL)
        {
            free(hist->data[hist->current_line]);
        }
        hist->data[hist->current_line] = ft_strdup(line);
        if (hist->keep_line != NULL)
        {
            free(hist->keep_line);
            hist->keep_line = NULL;
        }
        hist->current_line++;
        if (hist->current_line == hist->max_capacity)
        {
            hist->current_line = 0;
        }
        hist->search_pos = hist->current_line;
    }
}

/**
** Move in the history
** @param hist Current history of the shell
** @param line Command that needs to be saved
*/
static void move_in_hist(struct s_history *hist, int key)
{
    if (key == ARROW_UP)
    {
        if (hist->search_pos - 1 != hist->current_line)
        {
            if (hist->search_pos)
                hist->search_pos--;
            else
            {
                hist->search_pos = hist->max_capacity - 1;
                while (hist->search_pos != hist->current_line
                       && hist->data[hist->search_pos] == NULL)
                {
                    hist->search_pos--;
                }
                if (hist->search_pos == hist->current_line)
                    hist->search_pos = 0;
            }
        }
    }
    else
    {
        if (hist->search_pos != hist->current_line)
        {
            if (hist->search_pos == hist->max_capacity - 1)
                hist->search_pos = 0;
            else
                hist->search_pos += 1;
        }
    }
}

/**
** Retrieve command from the history
** @param hist Current history of the shell
** @param vect Vector that keep the current command
** @param key Pressed key
*/
size_t get_from_hist(struct s_history *hist, struct vector *vect, int key)
{
    // Keep the current line
    if (hist->keep_line == NULL)
    {
        hist->keep_line = ft_strdup(vect->data);
    }
    // We modify the history when it's necessary
    if (hist->search_pos != hist->current_line)
    {
        if (ft_strcmp(vect->data, hist->data[hist->search_pos]))
        {
            free(hist->data[hist->search_pos]);
            hist->data[hist->search_pos] = ft_strdup(vect->data);
        }
    }
    move_in_hist(hist, key);
    vector_clear(vect);
    // When we return on the current_line
    if (hist->search_pos == hist->current_line
        || hist->data[hist->search_pos] == NULL)
    {
        vector_insert_elms(vect, 0, hist->keep_line);
        hist->search_pos = hist->current_line;
        free(hist->keep_line);
        hist->keep_line = NULL;
    }
    else
    {
        vector_insert_elms(vect, 0, hist->data[hist->search_pos]);
    }
    return vect->size;
}

/**
** Free struct s_history
** @param hist Current history of the shell
*/
void free_history(struct s_history *hist)
{
    size_t index = 0;

    while (index < hist->max_capacity)
    {
        free(hist->data[index]);
        index++;
    }
    free(hist->data);
    free(hist);
}
