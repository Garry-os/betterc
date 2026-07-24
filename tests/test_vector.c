#include <betterc/vector.h>
#include <stdio.h>

int main() {
    Vector buffer = vector_new(v_type(float));
    vector_push(&buffer, 0.1f);
    vector_push(&buffer, 1.2f);
    vector_push(&buffer, 3.1f);
    vector_push(&buffer, 2.12f);
    float value = 0.5f;
    vector_push(&buffer, &value);

    for (usize i = 0; i < buffer.size; i++)
        printf("%f\n", vector_getv(float, &buffer, i));

    Vector reservedBuffer = vector_new(v_type(int));
    vector_reserve(&reservedBuffer, 10);

    return 0;
}
