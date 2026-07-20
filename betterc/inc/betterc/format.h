#pragma once
#include "types.h"
#include <betterc/string.h>

typedef enum {
    FORMAT_FLOAT,
    FORMAT_DOUBLE,
    FORMAT_UNSIGNED,
    FORMAT_SIGNED,
    FORMAT_BOOLEAN,
    FORMAT_CSTRING,
    FORMAT_STRING,
    FORMAT_POINTER
} FormatType;

typedef struct {
    FormatType type;
    union {
        float float_value;
        double double_value;
        u64 unsigned_value;
        i64 signed_value;
        bool boolean_value;
        char* cstring_value;
        String string_value;
        void* pointer_value;
    } value;
} FormatArg;

String format_impl(const char* fmt, FormatArg args[], usize argCount);
