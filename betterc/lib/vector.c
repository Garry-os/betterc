#include <betterc/vector.h>
#include <stdlib.h>
#include <string.h>

// 64 bytes
#define DEFAULT_ELEMENT_ALLOC (16)

Vector vector_new_reserve(usize elementSize, usize reservedSize) {
	Vector buffer;
    // Allocate memory
    buffer.capacity = reservedSize + DEFAULT_ELEMENT_ALLOC;
    buffer.data = (void*)malloc(buffer.capacity * elementSize);
    if (!buffer.data) {
        return (Vector){ 0, 0, 0, 0 };
    }

    buffer.size = reservedSize;
    buffer.elementSize = elementSize;

    return buffer;
}

Vector vector_new(usize elementSize) {
    Vector buffer = vector_new_reserve(elementSize, 0);

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



void vector_reserve(Vector* buffer, usize growthAmount) {
	grow_buffer_amount(buffer, growthAmount);
}
