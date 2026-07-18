#pragma once
#include "types.h"

typedef struct {
    void* data;
    usize size;
    usize capacity;
    usize elementSize;
} Vector;

Vector vector_new(usize elementSize);
void vector_free(Vector* buffer);

// Methods
void vector_push(Vector* buffer, const void* content);
void* vector_get(Vector* buffer, usize index);
