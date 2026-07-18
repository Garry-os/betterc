#pragma once

#if defined(__x86_64__)
#define BETTERC_ARCH_X86_64
#define BETTERC_ARCH_64BIT
#elif defined(__i386__)
#define BETTERC_ARCH_I386
#define BETTERC_ARCH_32BIT
#elif defined(__aarch64__)
#define BETTERC_ARCH_ARM64
#define BETTERC_ARCH_64BIT
#elif defined(__arm__)
#define BETTERC_ARCH_ARM
#define BETTERC_ARCH_32BIT
#endif
