#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <err.h>
#include <stdint.h>
#include <stdlib.h>

#define VECTOR_SIZE 64

/**
** Struct vector
*/
struct vector
{
    size_t size; /**< size_t size Size of the vector*/
    size_t capacity; /**< size_t capacity Maximum size of the vector */
    char *data; /**< char* data  Data part */
};

struct vector *vector_init(size_t capacity);
void double_capacity(struct vector *v);
void vector_push(struct vector *v, char elm);
int vector_pop(struct vector *v, char *elm);
void vector_clear(struct vector *v);
char vector_at(struct vector *v, size_t pos);
void vector_insert(struct vector *v, size_t pos, char elm);
void vector_insert_elms(struct vector *v, size_t pos, char *str);
int vector_remove(struct vector *v, size_t pos, char *elm);
int vector_remove_elms(struct vector *v, size_t pos, size_t len);
void vector_free(struct vector *v);

#endif
