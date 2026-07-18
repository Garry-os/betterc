#include <betterc/string.h>
#include <stdlib.h>

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
    free(string->data);
    string->data = 0;
    string->size = 0;
}

void string_append(String* string, const char* content) {
    // Calculate the needed size
    usize contentSize = bc_strlen(content);
    usize originalSize = string->size;
    char* data = realloc(string->data, originalSize + contentSize + 1);
    if (!data) {
        return;
    }
    string->data = data;
    string->size = originalSize + contentSize;
    // Copy over the string
    bc_strcpy(data + originalSize, content);
}
