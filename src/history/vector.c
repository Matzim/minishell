#include "vector.h"

/**
** Initialise the vector with the specified capacity.
** @param capacity Vector's capacity
** @return struct vector
*/
struct vector *vector_init(size_t capacity)
{
    struct vector *vec = malloc(sizeof(struct vector));

    if (vec == NULL)
    {
        errx(EXIT_FAILURE, "vector_init: allocation of vector failed !");
    }
    vec->size = 0;
    if (capacity == 0)
    {
        vec->capacity = VECTOR_SIZE;
    }
    else
    {
        vec->capacity = capacity;
    }
    vec->data = malloc(vec->capacity * sizeof(char));
    if (vec->data == NULL)
    {
        errx(EXIT_FAILURE, "vector_init: allocation of data array failed !");
    }
    return vec;
}

/**
** Double the capacity of the given vector.
** @param v Struct vector
*/
void double_capacity(struct vector *v)
{
    size_t new_capacity = v->capacity * 2;

    if (new_capacity < v->capacity)
    {
        errx(EXIT_FAILURE, "double_capacity: There is an overflow !");
    }
    v->capacity = new_capacity;
    v->data = (char *)realloc((void *)v->data, new_capacity * sizeof(char));
    if (v->data == NULL)
    {
        errx(EXIT_FAILURE,
             "double_capacity: allocation of data array failed !");
    }
}

/**
** Append character to the end of the vector.
** @param v Struct vector
** @param elm Character that must be inserted
*/
void vector_push(struct vector *v, char elm)
{
    if (v->size == v->capacity)
    {
        double_capacity(v);
    }
    v->data[v->size] = elm;
    v->size = v->size + 1;
}

/**
** Removes from the vector a single character at the end.
** @param v Struct vector
** @param elm Pointer to the removed character
** @return Boolean that indicate success
*/
int vector_pop(struct vector *v, char *elm)
{
    if (v->size == 0)
    {
        return 0;
    }
    *elm = v->data[v->size];
    v->size = v->size - 1;
    return 1;
}

/**
** Retrieve character at a given position.
** @param v Struct vector
** @param pos Position in the vector
*/
char vector_at(struct vector *v, size_t pos)
{
    if (v->size <= pos)
    {
        errx(EXIT_FAILURE, "vector_at: Out of bound !");
    }
    return v->data[pos];
}

/**
** Insert the element at the specified position.
** @param v Struct vector
** @param pos Position in the vector
** @param elm Pointer to the removed character
*/
void vector_insert(struct vector *v, size_t pos, char elm)
{
    size_t index;

    if (pos > v->size)
    {
        errx(EXIT_FAILURE, "vector_insert: Out of bound !");
    }
    if (v->size == v->capacity)
    {
        double_capacity(v);
    }
    index = v->size;
    while (index > pos)
    {
        v->data[index] = v->data[index - 1];
        index--;
    }
    v->data[pos] = elm;
    v->size = v->size + 1;
}

/**
** Insert string at the specified position.
** @param v Struct vector
** @param pos Position in the vector
** @param str Pointer to the string
*/
void vector_insert_elms(struct vector *v, size_t pos, char *str)
{
    size_t len = 0;
    size_t index = 0;
    char *array;

    if (pos > v->size)
    {
        errx(EXIT_FAILURE, "vector_insert: Out of bound !");
    }
    while (str[len] != '\0')
    {
        len++;
    }
    while (v->size + len > v->capacity)
    {
        double_capacity(v);
    }
    array = v->data;
    v->size += len;
    while (index + pos + len < v->size)
    {
        array[index + pos + len] = array[pos + index];
        index++;
    }
    index = 0;
    while (index < len)
    {
        array[pos + index] = str[index];
        index++;
    }
}

/**
** Remove the element at the specified position.
** @param v Struct vector
** @param pos Position in the vector
** @param elm Pointer to the removed character
*/
int vector_remove(struct vector *v, size_t pos, char *elm)
{
    char *array = v->data;

    if (pos >= v->size)
    {
        return 0;
    }
    *elm = array[pos];
    v->size = v->size - 1;
    while (pos < v->size)
    {
        array[pos] = array[pos + 1];
        pos++;
    }
    return 1;
}

/**
** Remove n * element(s) at the specified position.
** @param v Struct vector
** @param pos Position in the vector
** @param nb Number of characters to remove
*/
int vector_remove_elms(struct vector *v, size_t pos, size_t nb)
{
    char *array = v->data;
    size_t index = 0;

    if (pos + nb >= v->size)
    {
        return 0;
    }
    while (index + pos + nb < v->size)
    {
        array[pos + index] = array[pos + nb + index];
        index++;
    }
    v->size -= nb;
    return 1;
}

/**
** Clear the struct vector
** @param v Struct vector
*/
void vector_clear(struct vector *v)
{
    free(v->data);
    v->size = 0;
    v->capacity = VECTOR_SIZE;
    v->data = (char *)malloc(sizeof(char) * v->capacity);
    if (v->data == NULL)
    {
        errx(EXIT_FAILURE, "vector_clear: Not enough memory !");
    }
}

/**
** Free the vector
** @param v Struct vector
*/
void vector_free(struct vector *v)
{
    free(v->data);
    free(v);
}
