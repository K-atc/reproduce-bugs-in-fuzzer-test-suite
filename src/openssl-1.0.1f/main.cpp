#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

void usage(const char *argv[]) {
    fprintf(stderr, "usage: %s FILE\n", argv[0]);
    exit(1);
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        usage(argv);
    }
    const char *file_path = argv[1];

    // Open file
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        perror("Cannot open");
        exit(1);
    }

    // Get file size
    struct stat file_stat;
    fstat(fileno(file), &file_stat);
    size_t buf_size = file_stat.st_size;
    // printf("[*] Size of file %s: %ld\n", file_path, buf_size); // DEBUG:

    // Map file to read-only memory
    void *buf = mmap(NULL, buf_size, PROT_READ, MAP_SHARED, fileno(file), 0);
    if (buf == MAP_FAILED) {
        perror("Failed to mmap file");
        exit(1);
    }

    LLVMFuzzerTestOneInput(reinterpret_cast<const uint8_t *>(buf), buf_size);

    return 0;
}