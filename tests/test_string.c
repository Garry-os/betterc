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

    // Clone
    String stringClone = string_clone(&string);
    printf("String clone content: %s\n", stringClone.data);

    // Compare
    if (string_compare(&stringClone, &string)) {
        printf("Strings are equal (expected).\n");
    }
    else {
        printf("Strings are NOT equal\n");
    }

    // Clear string
    string_clear(&stringClone);
    printf("String after emptying: %s\n", stringClone.data);

    string_free(&string);
    string_free(&stringClone);

    return 0;
}
