#include <betterc/format.h>
#include <stdio.h>

#define FORMAT_MAX_BUFFER_SIZE 64

static inline void format_float(String* string, float value) {
    char buffer[FORMAT_MAX_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%f", value);
    string_append(string, buffer);
}

String format_impl(const char* fmt, FormatArg args[], usize argCount) {
    String string = string_new("");
    usize i = 0;
    usize currentArg = 0;
    while (fmt[i] != '\0') {
        // Check for formatters
        if (currentArg < argCount && fmt[i] == '{' && fmt[i + 1] == '}') {
            FormatArg arg = args[currentArg];
            // Print depending on the type
            switch (arg.type) {
                case FORMAT_FLOAT: format_float(&string, arg.value.float_value); break;
            }

            currentArg++;
            i++; // Skip formatter
        }
        else {
            // Append characters
            string_append_char(&string, fmt[i]);
        }

        i++;
    }

    return string;
}
