#pragma once
#include "types.h"
#include <betterc/string.h>

typedef enum {
    FORMAT_FLOAT,
} FormatType;

typedef struct {
    FormatType type;
    union {
        float float_value;
    } value;
} FormatArg;

String format_impl(const char* fmt, FormatArg args[], usize argCount);
