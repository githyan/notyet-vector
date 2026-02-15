#include "vector.h"
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define IN 1
#define OUT 0

int find_vector(Vector* vec, const int target)
{
    for (int i = 0; i < vec->size; i++) {
        if (vec->data[i] == target) {
            return i;
        }
    }
    // int left = 0;
    // int right = vec->size - 1;
    // while (left <= right) {
    //     int get_index = left + (right - left) / 2;
    //     int mid_value = vector_get(vec, get_index);
    //     if (mid_value == target) {
    //         return mid_value;
    //     } else if (mid_value < target) {
    //         left = get_index + 1;
    //     } else {
    //         right = get_index - 1;
    //     }
    // }
    return -1;
}

int delete_vector(Vector* vec, const int target, const int shrink)
{
    int index = find_vector(vec, target);
    printf("nilai index yang ingin ditargetkan: %d\n", index);
    int state;

    if (index != -1) {
        state = IN;
        for (int i = index; i <= vec->size; i++) {
            vec->data[i] = vec->data[i + 1];
        }
        vec->size--;
        if (shrink == 1 && vec->capacity > 1 && vec->size <= vec->capacity / 4) {
            shrink_capacity(vec);
        }
        return 1;
    } else {
        state = OUT;
        return 0;
    }
}

int vector_get(Vector* vec, const int index)
{
    if (vec == NULL) {
        err(errno, "Malloc :");
        free(vec);
        return -1;
    }

    if (index < 0 || index > vec->size - 1) {
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

    for (int i = 0; i < vec->size; i++) {
        printf("%d, ", vec->data[i]);
    }
    printf("\ncurrent vector->size :%d\n", vec->size);
    printf("current vector->capacity :%d\n", vec->capacity);
}
void shrink_capacity(Vector* vec)
{
    int* temp = vec->data;
    int new_capacity = vec->capacity / 2;
    vec->data = (int*)realloc(vec->data, new_capacity * sizeof(int));

    if (!vec->data) {
        err(errno, "Failed Reallocation Memory");
        vec->data = temp;
    }

    vec->capacity = new_capacity;
    for (int i = vec->size; i < vec->capacity; i++) {
        vec->data[i] = vec->data[i + 1];
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
