#include <betterc/fileapi.h>
#include <betterc/print.h>

int main() {
    // Open a file
    FileHandle* handle = NULL;
    FS_RESULT result = file_open(&handle, "test_file.txt", FILE_MODE_READ, 0);
    if (result != FS_RESULT_SUCCESS) {
        eprintln("Error: {}", fs_result_to_string(result));
        return -1;
    }

    usize fileSize = file_size(handle);
    char buffer[64];
    result = file_read(handle, fileSize, buffer);
    if (result != FS_RESULT_SUCCESS) {
        eprintln("Error: {}", fs_result_to_string(result));
        return -1;
    }

    for (usize i = 0; i < fileSize; i++) {
        putchar(buffer[i]);
    }

    file_close(&handle);

    // Test creating a file
    FileHandle* createHandle = NULL;
    result = file_open(&createHandle, "test_create.txt", FILE_MODE_WRITE, FILE_FLAG_CREATE);
    if (result != FS_RESULT_SUCCESS) {
        eprintln("Error: {}", fs_result_to_string(result));
        return -1;
    }

    // Write contents
    char content[] = "Contents written from test_fileapi";
    result = file_write(createHandle, sizeof(content) - 1, content);
    if (result != FS_RESULT_SUCCESS) {
        eprintln("Error: {}", fs_result_to_string(result));
        return -1;
    }

    file_close(&createHandle);

    return 0;
}
