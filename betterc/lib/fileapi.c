#include <betterc/fileapi.h>
#include <betterc/string.h>
#include <stdlib.h>
#include <errno.h>

static const char* file_attrib_lookup[16] = {
    [FILE_MODE_READ]                    =                   "r",
    [FILE_MODE_READ | FILE_MODE_WRITE]  =                   "r+",

    // Binary modes
    [FILE_MODE_READ | FILE_MODE_BINARY] =                   "rb",
    [FILE_MODE_WRITE | FILE_MODE_READ | FILE_MODE_BINARY] = "rb+"
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

FS_RESULT file_open(FileHandle** handle, const char* path, FileMode modes) {
    // Allocate memory for file handle
    *handle = (FileHandle*)malloc(sizeof(FileHandle));
    if (*handle == NULL) {
        return FS_RESULT_ALLOC_FAIL;
    }

    const char* attribs = modes_to_c_attribs(modes);
    FILE* file = fopen(path, attribs);
    if (!file) {
        // Free the handle
        free(*handle);

        return errno_to_fs_result();
    }
    (*handle)->handle = file;

    return FS_RESULT_SUCCESS;
}

// Read the content of the file one bytes each
FS_RESULT file_read(FileHandle* handle, usize readSize, void* buffer) {
    if (!handle) {
        return FS_RESULT_INVALID;
    }

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
