#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    bool needs_help = false;
    if (argc > 1) {
        needs_help = (0 == strcmp(argv[1], "-h"))
                  || (0 == strcmp(argv[1], "--help"));
    }

    if (argc != 3 || needs_help) {
        fprintf(needs_help ? stdout : stderr,
                "Atomically exchange two files.\n"
                "Usage: %s <file1> <file2>\n", argv[0]);
        return !needs_help;
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    int result = renameat2(AT_FDCWD, file1, AT_FDCWD, file2, RENAME_EXCHANGE);
    if (result < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }

    return 0;
}
