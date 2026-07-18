#include <betterc/string.h>
#include <stdlib.h>
#include <string.h>

static usize bc_strlen(const char* string) {
    usize len = 0;
    while (*string) {
        len++;
        string++;
    }

    return len;
}

static void bc_strcpy(char* dst, const char* src) {
    while (*src) {
        *dst = *src;
        src++;
        dst++;
    }

    *dst = '\0';
}

static int bc_strcmp(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }

    return (*a) - (*b);
}

String string_new(const char* content) {
    String string;
    // Allocate memory
    char* data = (char*)malloc(bc_strlen(content) + 1);
    if (!data) {
        return (String){ NULL, 0 };
    }
    bc_strcpy(data, content);
    string.data = data;
    string.size = bc_strlen(content);

    return string;
}

void string_free(String* string) {
    if (string->data)
        free(string->data);
    string->data = 0;
    string->size = 0;
}

void string_append(String* string, const char* content) {
    // Calculate the needed size
    usize contentSize = bc_strlen(content);
    usize originalSize = string->size;
    char* data = (char*)realloc(string->data, originalSize + contentSize + 1);
    if (!data) {
        return;
    }
    string->data = data;
    string->size = originalSize + contentSize;
    // Copy over the string
    bc_strcpy(data + originalSize, content);
}

String string_clone(const String* src) {
    String target;
    // Allocate memory
    usize srcSize = src->size;
    char* data = (char*)malloc(srcSize + 1);
    if (!data) {
        return (String){ 0, 0 };
    }
    target.data = data;
    target.size = srcSize;

    // Copy over the data
    bc_strcpy(target.data, src->data);

    return target;
}

// Returns true if equal
// otherwise false
bool string_compare(const String* a, const String* b) {
    if (bc_strcmp(a->data, b->data) == 0) {
        return true;
    }

    return false;
}

// Clear the whole string's buffer
// Also resets the size to 0
void string_clear(String* string) {
    // Reset the data
    memset(string->data, 0, string->size);
    string->size = 0;
}

char string_at(const String* string, usize index) {
    return string->data[index];
}
