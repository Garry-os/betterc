#pragma once
#include <stdio.h>
#include <betterc/types.h>

// Used for both fileapi.h and fsapi.h
typedef enum {
    FS_RESULT_SUCCESS = 0,  // Success
    FS_RESULT_NOT_FOUND,    // File not found
    FS_RESULT_ALLOC_FAIL,   // Failed to allocate file handle
    FS_RESULT_PERMISSION,   // Permission issues
    FS_RESULT_ISDIR,        // Is a directory
    FS_RESULT_NOTDIR,       // Isn't a directory
    FS_RESULT_ERRIO,        // I/O errors
    FS_RESULT_INVALID,      // Invalid flags/parameters
    FS_RESULT_EOF,          // End of file
    FS_RESULT_UNKNOWN,      // Unknown error
} FS_RESULT;

const char* fs_result_to_string(FS_RESULT result);

// Bitmask
// File attributes can be OR to combine
// For example FILE_MODE_READ | FILE_MODE_WRITE = RW
typedef enum {
    FILE_MODE_READ =   (1 << 0),
    FILE_MODE_WRITE =  (1 << 1),
    FILE_MODE_BINARY = (1 << 2)
} FileMode;

typedef struct {
    FileMode modes;
    FILE* handle;
} FileHandle;

FS_RESULT file_open(FileHandle** handle, const char* path, FileMode modes);
FS_RESULT file_read(FileHandle* handle, usize readSize, void* buffer);
usize file_size(FileHandle* handle);
void file_close(FileHandle** handle);
