#include "vector.h"
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vector_get(Vector* vec, const int index)
{
    if (vec == NULL) {
        err(errno, "Malloc :");
        free(vec);
        return -1;
    }

    if (index < 0 || index >= vec->size) {
        fprintf(stderr, "index out of Bound at: %d\n", index);
        return -1;
    }

    return vec->data[index];
}
void vector_add(Vector* vec, const int value)
{
    if (!vec)
        err(errno, "Failed Reallocation Memory");

    if (vec->size >= vec->capacity)
        grow_capacity(vec);

    vec->data[vec->size] = value;
    vec->size++;
}
void vector_to_back(Vector* vec, int value)
{
    if (!vec) {
        err(errno, "Allocation is Failed");
    }
    int get_capacity = vec->capacity - 1;
    for (int i = 0; i < get_capacity; i++) {
        vec->data[get_capacity] = value;
    }
    get_capacity--;
    vec->size++;
}
void vector_print(Vector* vec)
{
    if (!vec)
        exit(-1);

    for (int i = 0; i < vec->capacity; i++) {
        printf("%d, ", vec->data[i]);
    }
}

void grow_capacity(Vector* vec)
{
    int* temp = vec->data;
    int new_capacity = vec->capacity * 2;
    vec->data = (int*)realloc(vec->data, new_capacity * sizeof(int));

    if (!vec->data) {
        err(errno, "Failed Reallocation Memory");
        vec->data = temp;
    }

    vec->capacity = new_capacity;
    for (int i = vec->size; i < vec->capacity; i++) {
        vec->data[i] = 0;
    }
}

void vector_init(Vector* vec, size_t size, size_t capacity)
{
    if (vec == NULL) {
        err(errno, "Failed Reallocation Memory");
        exit(1);
    }
    add_component(vec, size, capacity);
    if (!vec->data)
        free(vec);

    return;
}

Vector* create_vector(int size, int capacity)
{
    Vector* vec;
    if ((vec = (Vector*)malloc(capacity * sizeof(Vector))) == NULL) {
        err(errno, "Failed to allocation Memory");
        return NULL;
    }

    add_component(vec, size, capacity);

    if (!vec->data) {
        free(vec);
        vec = NULL;
    }
    return vec;
}
