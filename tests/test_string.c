#include <betterc/io.h>
#include <betterc/string.h>
#include <stdio.h>

int main() {
    printf("String test\n");

    // Test strings
    String string = string_new("Hello world from custom string!");
    printf("%s\n", string.data);

    // Append
    string_append(&string, " Appended content");

    printf("String after appending.\n");
    printf("%s\n", string.data);

    string_free(&string);

    return 0;
}
