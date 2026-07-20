#include <betterc/compiler.h>
#include <betterc/format.h>
#include <stdio.h>

#define FORMAT_MAX_BUFFER_SIZE 64

static inline void format_float(String* string, float value) {
    char buffer[FORMAT_MAX_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%f", value);
    string_append(string, buffer);
}
static inline void format_double(String* string, double value) {
    char buffer[FORMAT_MAX_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%lf", value);
    string_append(string, buffer);
}
static inline void format_unsigned(String* string, u64 value) {
    char buffer[FORMAT_MAX_BUFFER_SIZE];
#ifndef BETTERC_COMPILER_MSVC
    snprintf(buffer, sizeof(buffer), "%lu", value);
#else
    sprintf(buffer, sizeof(buffer), "%llu", value);
#endif
    string_append(string, buffer);
}
static inline void format_signed(String* string, i64 value) {
    char buffer[FORMAT_MAX_BUFFER_SIZE];
#ifndef BETTERC_COMPILER_MSVC
    snprintf(buffer, sizeof(buffer), "%ld", value);
#else
    sprintf(buffer, sizeof(buffer), "%lld", value);
#endif
    string_append(string, buffer);
}
static inline void format_boolean(String* string, bool value) {
    if (value)
        string_append(string, "true");
    else
        string_append(string, "false");
}

static inline void format_cstring(String* string, const char* cstr) {
    string_append(string, cstr);
}
static inline void format_string(String* target, const String* format) {
    string_append(target, format->data);
}
static void format_pointer(String* string, const void* ptr) {
    char buffer[FORMAT_MAX_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%p", ptr);
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
                case FORMAT_DOUBLE: format_double(&string, arg.value.double_value); break;
                case FORMAT_UNSIGNED: format_unsigned(&string, arg.value.unsigned_value); break;
                case FORMAT_SIGNED: format_signed(&string, arg.value.signed_value); break;
                case FORMAT_BOOLEAN: format_boolean(&string, arg.value.boolean_value); break;
                case FORMAT_CSTRING: format_cstring(&string, arg.value.cstring_value); break;
                case FORMAT_STRING: format_string(&string, &arg.value.string_value); break;
                case FORMAT_POINTER: format_pointer(&string, arg.value.pointer_value); break;
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
