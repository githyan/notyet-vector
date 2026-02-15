#include "../vector.h"
#include <assert.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Vector* vector = create_vector(0, 3);
    assert(vector);

    // assert(vector_get(vector, 3) == 0);
    for (int i = 0; i <= 1000; i++) {
        vector_add(vector, i);
    }
    if (vector != NULL) {
        free(vector);
        free(vector->data);
    }

    return 0;
    // for (int i = 0; i <= 1000; i++)
    // assert(vector_get(vector, 10) == 1);
}
