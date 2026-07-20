#pragma once
#include "types.h"

// Fast string creation
// Stack-allocated
#define str(content) ((String){ content, sizeof(content), sizeof(content) })

// Wrappers
#define string_append_char(string, ch) string_append_count(string, &ch, 1)

typedef struct {
    char* data;
    usize size; // Does not contain the NULL terminator
    usize capacity; // Does not contain NULL terminator
} String;

String string_new(const char* content);
void string_free(String* string);

// Methods
String string_clone(const String* src);
void string_append(String* string, const char* content);
void string_append_count(String* string, const char* content, usize count);
bool string_compare(const String* a, const String* b);
void string_clear(String* string);
char string_at(const String* string, usize index);
void string_reserve(String* string, usize newCapacity);
