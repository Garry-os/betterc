#pragma once
#include "format.h"
#include <stdio.h>

#define print(fmt, ...) fputs(format(fmt __VA_OPT__(,) __VA_ARGS__).data, stdout)
#define println(fmt, ...) fputs(format(fmt __VA_OPT__(,) __VA_ARGS__).data, stdout)

// Error printing
#define eprint(fmt, ...) fputs(format(fmt __VA_OPT__(,) __VA_ARGS__).data, stderr)
#define eprintln(fmt, ...) fputs(format(fmt __VA_OPT__(,) __VA_ARGS__).data, stderr)

