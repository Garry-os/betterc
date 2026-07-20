#pragma once

// Detect the compiler
#if defined(_GNUC)
#define BETTERC_COMPILER_GCC
#elif defined(__clang__)
#define BETTERC_COMPILER_CLANG
#elif defined(_MSC_VER)
#define BETTERC_COMPILER_MSVC
#endif

// Attribute-specific
#if defined(BETTERC_COMPILER_GCC) || defined(BETTERC_COMPILER_CLANG)
#define BETTERC_ATTR_CLEANUP(func) __attribute__((cleanup(func)))
#elif BETTERC_COMPILER_MSVC
// MSVC doesn't have it
#endif
