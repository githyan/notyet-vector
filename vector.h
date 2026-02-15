#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
struct Vector {
    int* data;
    int size;
    int capacity;
};

typedef struct Vector Vector;

static inline void add_component(Vector* vec, int size, int capacity)
{
    vec->size = size;
    vec->capacity = capacity;
    vec->data = (int*)calloc(vec->capacity, sizeof(int));
}

void vector_init(Vector* vec, size_t size, size_t capacity);
// void vector_resize();
void vector_add(Vector* vec, const int value);
void vector_to_back(Vector* vec, int value);
void vector_print(Vector* vec);
void grow_capacity(Vector* vec);
void shrink_capacity(Vector* vec);
int vector_get(Vector* vec, const int index);
int find_vector(Vector* vec, const int target);
int delete_vector(Vector* vec, const int target, const int shrink);
// Vector vector_free();
Vector* create_vector(int size, int capacity);

#endif // !VECTOR_H
