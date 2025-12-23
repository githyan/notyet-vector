#include "vector.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 0
#define INITIAL_CAPACITY 3

struct Command_entry {
    char* name;
    void (*func)(Vector*, int);
} Command_entry;

static inline int get_args_digit(void (*f)(Vector*, int), Vector*, const char**, int, int);

/* Creating an empty returns to assign the vector_get(), so that is initializing
 * as an argument parameter of get_args_digit() to make it more responsible,
 * to get the code segment could be readable and well-maintained.
 */
void get_vector_to_index(Vector* vector, const int index)
{
    int result = vector_get(vector, index);
    printf("berhasil mendapatkan :%d\n", result);
}

void get_vector_print(Vector* vector, const int index)
{
    vector_print(vector);
}

void get_vector_create(Vector* vector, const int a)
{
    create_vector(vector->size, vector->capacity);
}

int main(int argc, char** argv)
{
    Vector* p_vector = create_vector(INITIAL_SIZE, INITIAL_CAPACITY);

    /* Lookup table for command list entries */
    struct Command_entry command[] = {
        { "--add", vector_add },
        { "--print-array", get_vector_print },
        { "--get-index", get_vector_to_index },
        { "--init", get_vector_create }
    };

    for (int i = 0; i < argc; i++) {
        if (i < 3 && i == 0) {
            fprintf(stderr, "Usage: %s <command> <value> [<n>]\n", argv[0]);
        } else {
            if (strcmp(argv[i], command[0].name) == 0) {
                get_args_digit(command[0].func, p_vector, argv, argc, i); // i++;
            } else if (strcmp(argv[i], command[1].name) == 0) {
                vector_print(p_vector);
            } else if (strcmp(argv[i], command[2].name) == 0) {
                get_args_digit(command[2].func, p_vector, argv, argc, i);
            }
        }
    }

    if (p_vector != NULL) {
        free(p_vector->data);
        p_vector->data = NULL;
        free(p_vector);
        p_vector = NULL;
    }

    return 0;
}

static inline int get_args_digit(void (*f)(Vector*, int), Vector* _vector, const char** argv, int argc, int size)
{
    int convert_args_digit = atoi(argv[size + 1]);
    if (size + 1 < argc) {
        // printf("[DEBUG] Sedang menambahkan angka: %d\n", convert_args_digit); // Cek ini muncul gak?
        f(_vector, convert_args_digit);
        size++;
        return convert_args_digit;
    } else {
        fprintf(stderr, "Error: Command '%s' must need an argument is number as value!\n", argv[size]);
        return -1;
    }
}
