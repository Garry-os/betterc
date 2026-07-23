#pragma once

#if defined(__linux__)
#define BETTERC_PLATFORM_LINUX
#elif defined(__APPLE__)
#define BETTERC_PLATFORM_APPLE
#elif defined(_WIN32)
#define BETTERC_PLATFORM_WIN32
#endif

#if defined(BETTERC_PLATFORM_WIN32)
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif
