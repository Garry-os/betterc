#include <betterc/fileapi.h>
#include <betterc/string.h>
#include <stdlib.h>
#include <errno.h>
#include <betterc/platform.h>

static const char* file_attrib_lookup[] = {
    [FILE_MODE_READ]                    = "r",
    [FILE_MODE_WRITE]                   = "r+",
    [FILE_MODE_READ | FILE_MODE_WRITE]  = "r+",
    [FILE_MODE_APPEND]                  = "a",
    [FILE_MODE_APPEND | FILE_MODE_READ] = "a+",

    // Binary modes
    [FILE_MODE_READ | FILE_MODE_BINARY]                     = "rb",
    [FILE_MODE_WRITE | FILE_MODE_BINARY]                    = "rb+",
    [FILE_MODE_WRITE | FILE_MODE_READ | FILE_MODE_BINARY]   = "rb+",
    [FILE_MODE_APPEND | FILE_MODE_BINARY]                   = "ab",
    [FILE_MODE_APPEND | FILE_MODE_READ  | FILE_MODE_BINARY] = "ab+"
};

const char* modes_to_c_attribs(FileMode modes) {
    const char* attrib = file_attrib_lookup[modes];
    if (!attrib) return NULL;

    return attrib;
}

FS_RESULT errno_to_fs_result() {
    switch (errno) {
        case ENOENT:    return FS_RESULT_NOT_FOUND;
        case EACCES:    return FS_RESULT_PERMISSION;
        case EISDIR:    return FS_RESULT_ISDIR;
        case ENOTDIR:   return FS_RESULT_NOTDIR;
        case EIO:       return FS_RESULT_ERRIO;
        default:        return FS_RESULT_UNKNOWN;
    }
}

const char* fs_result_to_string(FS_RESULT result) {
    switch (result) {
        case FS_RESULT_SUCCESS:     return "Success";
        case FS_RESULT_NOT_FOUND:   return "File not found";
        case FS_RESULT_ALLOC_FAIL:  return "Failed to allocate file handle";
        case FS_RESULT_PERMISSION:  return "Permission denied";
        case FS_RESULT_ISDIR:       return "Is a directory";
        case FS_RESULT_NOTDIR:      return "Is not a directory";
        case FS_RESULT_ERRIO:       return "I/O errors";
        case FS_RESULT_INVALID:     return "Invalid flags/parameters";
        case FS_RESULT_EOF:         return "End of file";
        case FS_RESULT_UNKNOWN:     return "Unknown error";
        default:                    return "Invalid FS_RESULT";
    }
}

static inline bool check_file_existence(const char* path) {
    return access(path, F_OK) == 0;
}

FS_RESULT file_open(FileHandle** handle, const char* path, FileMode modes, FileFlags flags) {
    // Check for file's existence
    // Create a file if CREATE flag is set
    if (!check_file_existence(path)) {
        if ((flags & FILE_FLAG_CREATE) != 0) {
            // Create the file
            FILE* tmp_file = fopen(path, "w");
            fclose(tmp_file);
        }
        else {
            return FS_RESULT_NOT_FOUND;
        }
    }

    // Allocate memory for file handle
    *handle = (FileHandle*)malloc(sizeof(FileHandle));
    if (*handle == NULL) {
        return FS_RESULT_ALLOC_FAIL;
    }

    const char* attribs = modes_to_c_attribs(modes);
    if (!attribs) {
        // Invalid attributes
        return FS_RESULT_INVALID;
    }

    FILE* file = fopen(path, attribs);
    if (!file) {
        // Free the handle
        free(*handle);

        return errno_to_fs_result();
    }
    (*handle)->handle = file;
    (*handle)->modes = modes;

    return FS_RESULT_SUCCESS;
}

// Read the content of the file one bytes each
FS_RESULT file_read(FileHandle* handle, usize readSize, void* buffer) {
    if (!handle)
        return FS_RESULT_INVALID;
    if ((handle->modes & FILE_MODE_READ) == 0)
        return FS_RESULT_INVALID;

    usize sizeRead = fread(buffer, 1, readSize, handle->handle);
    if(sizeRead != readSize) {
        if (ferror(handle->handle)) {
            return errno_to_fs_result();
        }
        else if (feof(handle->handle)) {
            return FS_RESULT_EOF;
        }
        else {
            return FS_RESULT_UNKNOWN;
        }
    }

    return FS_RESULT_SUCCESS;
}

FS_RESULT file_write(FileHandle* handle, usize writeSize, void* buffer) {
    // Handle invalid cases
    if (!handle)
        return FS_RESULT_INVALID;
    if ((handle->modes & FILE_MODE_WRITE) == 0 && (handle->modes & FILE_MODE_APPEND) == 0)
        return FS_RESULT_INVALID;

    usize sizeWritten = fwrite(buffer, 1, writeSize, handle->handle);
    if (sizeWritten != writeSize)
        return errno_to_fs_result();

    return FS_RESULT_SUCCESS;
}

usize file_size(FileHandle* handle) {
    if (!handle) {
        return FS_RESULT_INVALID;
    }

    // Seek to the end of the file
    fseek(handle->handle, 0, SEEK_END);
    usize size = ftell(handle->handle); // Get the size
    rewind(handle->handle); // Go back

    return size;
}

// Close the file handle
// Also free the handle
void file_close(FileHandle** handle) {
    if (*handle) {
        // Close the file
        fclose((*handle)->handle);
        // Free the handle
        free(*handle);
        *handle = 0;
    }
}
