#pragma once
#include "architecture.h"

// Unsigned
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned u32;
typedef unsigned long u64;

// Signed
typedef char i8;
typedef short int i16;
typedef int i32;
typedef long int i64;

// Size
#if defined(BETTERC_ARCH_64BIT)
typedef u64 usize;
typedef i64 isize;
#elif defined(BETTERC_ARCH_32BIT)
typedef i32 usize;
typedef i64 usize;
#endif
