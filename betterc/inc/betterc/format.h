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

// Argument types
static inline FormatArg format_arg_float(float value) {
    return (FormatArg){ .type = FORMAT_FLOAT, .value.float_value = value };
}

#define _FORMAT_MAKE_ARGS(x) _Generic((x), \
    float: format_arg_float \
)(x)

#define _FORMAT_NUM_ARGS_(_unused, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                          _11, _12, _13, _14, _15, _16, N, ...) N
#define _FORMAT_NUM_ARGS(_unused, ...) \
    _FORMAT_NUM_ARGS_( __VA_OPT__(,) __VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, \
                      9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define _CONCAT_(a, b) a##b
#define _CONCAT(a, b) _CONCAT_(a, b)

// Mapping macros
#define _FORMAT_MAP_0(...)
#define _FORMAT_MAP_1(f, a) f(a)
#define _FORMAT_MAP_2(f, a, b) f(a), f(b)
#define _FORMAT_MAP_3(f, a, b, c) f(a), f(b), f(c)
#define _FORMAT_MAP_4(f, a, b, c, d) f(a), f(b), f(c), f(d)
#define _FORMAT_MAP_5(f, a, b, c, d, e) f(a), f(b), f(c), f(d), f(e)
#define _FORMAT_MAP_6(f, a, b, c, d,  e, g) f(a), f(b), f(c), f(d), f(e), f(g)
#define _FORMAT_MAP_7(f, a, b, c, d, e, g, h) \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h)
#define _FORMAT_MAP_8(f, a, b, c, d, e, g, h, i) \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i)
#define _FORMAT_MAP_9(f, a, b, c, d, e, g, h, i, j) \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j)
#define _FORMAT_MAP_10(f, a, b, c, d, e, g, h, i, j, k) \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j), f(k)
#define _FORMAT_MAP_11(f, a, b, c, d, e, g, h, i, j, k, l) \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j), f(k), f(l)
#define _FORMAT_MAP_12(f, a, b, c, d, e, g, h, i, j, k, l, m) \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j), f(k), f(l), f(m)
#define _FORMAT_MAP_13(f, a, b, c, d, e, g, h, i, j, k, l, m, n) \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j), f(k), f(l), f(m), f(n)
#define _FORMAT_MAP_14(f, a, b, c, d, e, g, h, i, j, k, l, m, n, o)           \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j), f(k), f(l), f(m), \
        f(n), f(o)
#define _FORMAT_MAP_15(f, a, b, c, d, e, g, h, i, j, k, l, m, n, o, p)        \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j), f(k), f(l), f(m), \
        f(n), f(o), f(p)
#define _FORMAT_MAP_16(f, a, b, c, d, e, g, h, i, j, k, l, m, n, o, p, q)     \
    f(a), f(b), f(c), f(d), f(e), f(g), f(h), f(i), f(j), f(k), f(l), f(m), \
        f(n), f(o), f(p), f(q)

#define _FORMAT_MAP(f, ...) \
    _CONCAT(_FORMAT_MAP_, _FORMAT_NUM_ARGS( __VA_OPT__(,) __VA_ARGS__))(f __VA_OPT__(,) __VA_ARGS__)

#define _FORMAT_VARGS_SELECT(e, n, ...)                                             \
    _FORMAT_NUM_ARGS( __VA_OPT__(,) __VA_ARGS__, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, \
                e)
#define _MAKE_ARGLIST(...) \
    (FormatArg[]) { _FORMAT_MAP(_FORMAT_MAKE_ARGS __VA_OPT__(,) __VA_ARGS__) }
#define _MAKE_NULL(...) NULL
#define _EXPAND(e) e

#define _FORMAT_ARGS(fmt, ...) \
    (fmt), \
        _EXPAND(_FORMAT_VARGS_SELECT(_MAKE_NULL, _MAKE_ARGLIST __VA_OPT__(,) __VA_ARGS__)(__VA_ARGS__)), \
        _FORMAT_NUM_ARGS( __VA_OPT__(,) __VA_ARGS__)

#define format(fmt, ...) \
    format_impl(_FORMAT_ARGS((fmt) __VA_OPT__(,) __VA_ARGS__))


String format_impl(const char* fmt, FormatArg args[], usize argCount);
