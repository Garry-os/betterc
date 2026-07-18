#pragma once

#if defined(__x86_64__)
#define BETTERC_ARCH_X86_64
#elif defined(__i386__)
#define BETTERC_ARCH_I386
#elif defined(__arm__)
#define BETTERC_ARCH_ARM
#elif defined(__aarch64__)
#define BETTERC_ARCH_ARM64
#endif
