#include <betterc/vector.h>
#include <stdlib.h>
#include <string.h>

// 64 bytes
#define DEFAULT_ELEMENT_ALLOC (16)

Vector vector_new(usize elementSize) {
    Vector buffer;
    // Allocate memory
    buffer.capacity = DEFAULT_ELEMENT_ALLOC;
    buffer.data = (void*)malloc(buffer.capacity * elementSize);
    if (!buffer.data) {
        return (Vector){ 0, 0, 0, 0 };
    }

    buffer.size = 0;
    buffer.elementSize = elementSize;

    return buffer;
}

void vector_free(Vector* buffer) {
    // Free the data
    if (buffer->data)
        free(buffer->data);
    // Reset everything
    buffer->data = 0;
    buffer->capacity = 0;
    buffer->size = 0;
    buffer->elementSize = 0;
}

static void grow_buffer_amount(Vector* buffer, usize growthAmount) {
	buffer->capacity += growthAmount;
	void* data = (void*)realloc(buffer->data, buffer->capacity * buffer->elementSize);
	if (!data)
		return;
	buffer->data = data;
}

// Only grows if needed
static void grow_buffer(Vector* buffer) {
    if (buffer->size < buffer->capacity)
        return;

    grow_buffer_amount(buffer, DEFAULT_ELEMENT_ALLOC);
}

void vector_push_impl(Vector* buffer, const void* content) {
    grow_buffer(buffer);
    memcpy((u8*)buffer->data + buffer->size * buffer->elementSize, content, buffer->elementSize);
    buffer->size += 1;
}

void* vector_get(Vector* buffer, usize index) {
    // Bound checking
    if (index >= buffer->size)
        return NULL;

    return (void*)((u8*)buffer->data + index * buffer->elementSize);
}

void vector_pushfloat(Vector* buffer, float value) {
    vector_push_impl(buffer, &value);
}

void vector_pushdouble(Vector* buffer, double value) {
    vector_push_impl(buffer, &value);
}

// Unsigned integers
void vector_pushu8(Vector* buffer, u8 value) {
    vector_push_impl(buffer, &value);
}

void vector_pushu16(Vector* buffer, u16 value) {
    vector_push_impl(buffer, &value);
}

void vector_pushu32(Vector* buffer, u32 value) {
    vector_push_impl(buffer, &value);
}

void vector_pushu64(Vector* buffer, u64 value) {
    vector_push_impl(buffer, &value);
}

void vector_pushi8(Vector* buffer, i8 value) {
    vector_push_impl(buffer, &value);
}

void vector_pushi16(Vector* buffer, i16 value) {
    vector_push_impl(buffer, &value);
}

void vector_pushi32(Vector* buffer, i32 value) {
    vector_push_impl(buffer, &value);
}

void vector_pushi64(Vector* buffer, i64 value) {
    vector_push_impl(buffer, &value);
}

void vector_reserve(Vector* buffer, usize growthAmount) {
	grow_buffer_amount(buffer, growthAmount);
}
