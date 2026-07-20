#include <betterc/format.h>
#include <stdio.h>

int main() {
    String testString = str("Real string btw.");
    FormatArg args[] = { {.type = FORMAT_POINTER, .value.pointer_value = (void*)0xDEADBEEF}, {.type = FORMAT_STRING, .value.string_value = testString} };
    usize argCount = 2;

    String string = format_impl("String: {} {}", args, argCount);
    printf("%s\n", string.data);

    return 0;
}
