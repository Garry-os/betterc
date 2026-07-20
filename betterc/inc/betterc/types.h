#pragma once
#include "architecture.h"
#include <stdbool.h>
#include <stdint.h>

// Unsigned
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Size
#if defined(BETTERC_ARCH_64BIT)
typedef u64 usize;
typedef i64 isize;
#elif defined(BETTERC_ARCH_32BIT)
typedef u32 usize;
typedef i32 isize;
#endif

// Unused
#define UNUSED(x) ((void)x)
