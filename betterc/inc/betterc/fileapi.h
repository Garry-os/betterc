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

/**
 * @brief Convert FS_RESULT into a string message.
 *
 * @param[in] result The result of a function.
 * @return A string message.
 */
const char* fs_result_to_string(FS_RESULT result);

/**
 * @brief Opens a file.
 *
 * @param[out] handle The file handle received on success.
 * @param[in] path Path to the file.
 * @param[in] modes Access modes to the file.
 * @return FS_RESULT_SUCCESS on success, otherwise an error code.
 */
FS_RESULT file_open(FileHandle** handle, const char* path, FileMode modes);

/**
 * @brief Reads a file.
 *
 * @param[in] handle File handle.
 * @param[in] readSize Amount of bytes to read.
 * @param[out] buffer Buffer to output to.
 * @return FS_RESULT_SUCCESS on success, otherwise an error code.
 */
FS_RESULT file_read(FileHandle* handle, usize readSize, void* buffer);

/**
 * @brief Get a file size.
 *
 * @param[in] handle File handle.
 * @return File size.
 */
usize file_size(FileHandle* handle);

/**
 * @brief Close a file.
 *
 * @param[in] handle FileHandle
 */
void file_close(FileHandle** handle);
