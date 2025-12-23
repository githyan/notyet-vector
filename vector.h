#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
struct Vector {
    int* data;
    int size;
    int capacity;
};

typedef struct Vector Vector;
void vector_init(Vector* vec, size_t size, size_t capacity);
// void vector_resize();
void vector_add(Vector* vec, const int value);
void vector_to_back(Vector* vec, int value);
void vector_print(Vector* vec);
void grow_capacity(Vector* vec);
int vector_get(Vector* vec, const int index);
// Vector vector_free();
Vector* create_vector(int size, int capacity);

#endif // !VECTOR_H
