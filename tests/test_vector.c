#include <betterc/vector.h>
#include <stdio.h>

int main() {
    Vector buffer = vector_new(sizeof(int));
    for (int i = 0; i < 10; i++)
        vector_push(&buffer, &i);

    for (usize i = 0; i < buffer.size; i++)
        printf("%d\n", vector_getv(int, &buffer, i));

    return 0;
}
