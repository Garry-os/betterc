#include <betterc/format.h>
#include <stdio.h>

int main() {
    FormatArg args[] = { {.type = FORMAT_FLOAT, .value.float_value = 0.5f} };
    usize argCount = 1;

    String string = format_impl("Float: {}", args, argCount);
    printf("%s\n", string.data);

    return 0;
}
