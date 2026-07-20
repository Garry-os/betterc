#pragma once
#include "format.h"
#include <stdio.h>

#define print(fmt, ...) printf("%s", format(fmt __VA_OPT__(,) __VA_ARGS__).data)
#define println(fmt, ...) printf("%s\n", format(fmt __VA_OPT__(,) __VA_ARGS__).data)
