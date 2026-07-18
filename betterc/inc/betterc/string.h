#pragma once
#include "types.h"

typedef struct {
    char* data;
    usize size; // Does not contain the NULL terminator
} String;

String string_new(const char* content);
void string_free(String* string);

// Methods
void string_append(String* string, const char* content);
