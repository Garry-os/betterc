#include <betterc/fileapi.h>
#include <betterc/print.h>

int main() {
    // Open a file
    FileHandle* handle = NULL;
    FS_RESULT result = file_open(&handle, "test_file.txt", FILE_MODE_READ);
    if (result != FS_RESULT_SUCCESS) {
        eprintln("Error: {}", fs_result_to_string(result));
        return -1;
    }

    usize fileSize = file_size(handle);
    char buffer[64];
    result = file_read(handle, fileSize, buffer);
    if (result != FS_RESULT_SUCCESS)
        eprintln("Error: {}", fs_result_to_string(result));
        return -1;
    }
    // println("File content: {}\n", buffer);
    for (usize i = 0; i < fileSize; i++) {
        putchar(buffer[i]);
    }

    file_close(&handle);

    return 0;
}
