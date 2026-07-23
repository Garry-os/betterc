#pragma once
#include <stdio.h>
#include <betterc/types.h>

#define BIT(x) (1 << x)

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

/**
 * @brief File access modes for opening files.
 */
typedef enum {
    /** Open for read mode. */
    FILE_MODE_READ      = BIT(0),

    /** Open for write mode. */
    FILE_MODE_WRITE     = BIT(1),

    /** Open using binary mode. */
    FILE_MODE_BINARY    = BIT(2),

    /** Append all writes to the end of the file. */
    FILE_MODE_APPEND    = BIT(3),
} FileMode;

/**
 * @brief File opening flags for opening files.
 */
typedef enum {
    /** Create a file if it doesn't exist. */
    FILE_FLAG_CREATE = BIT(0),
} FileFlags;

/**
 * @brief Represents a file.
 */
typedef struct {
    /** File access modes. */
    FileMode modes;

    /** The FILE* handle. User should NOT modify handle. */
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
 * @note File flags can't be standalone, they need to be paired with modes.
 *
 * @param[out] handle The file handle received on success.
 * @param[in] path Path to the file.
 * @param[in] modes Access modes to the file.
 * @param[in] flags File flags.
 * @return FS_RESULT_SUCCESS on success, otherwise an error code.
 */
FS_RESULT file_open(FileHandle** handle, const char* path, FileMode modes, FileFlags flags);

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
 * @brief Writes to a file.
 *
 * @param[in] handle File handle.
 * @param[in] writeSize Amount of bytes to write.
 * @param[in] buffer The input buffer.
 */
FS_RESULT file_write(FileHandle* handle, usize writeSize, void* buffer);

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
