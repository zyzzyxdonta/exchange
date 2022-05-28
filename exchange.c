#ifdef __linux__
#define _GNU_SOURCE
#define EXCHANGE_FUNCTION(file1, file2) \
    renameat2(AT_FDCWD, (file1), AT_FDCWD, (file2), RENAME_EXCHANGE);
#elif __APPLE__
#define EXCHANGE_FUNCTION(file1, file2) \
    renameatx_np(AT_FDCWD, (file1), AT_FDCWD, (file2), RENAME_SWAP);
#else
#error "Target not supported"
#endif

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    bool needs_help = argc == 1;
    if (argc > 1) {
        needs_help = (0 == strcmp(argv[1], "-h"))
                  || (0 == strcmp(argv[1], "--help"));
    }

    if (argc != 3 || needs_help) {
        printf("Atomically exchange two files.\n"
               "\n"
               "Usage:\n"
               "        %s FILE1 FILE2\n"
               "        %s [-h | --help]\n",
               argv[0], argv[0]);
        return !needs_help;
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    int result = EXCHANGE_FUNCTION(file1, file2);
    if (result < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    return 0;
}
