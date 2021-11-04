#define _GNU_SOURCE

#include <fcntl.h>
#include <getopt.h>
#include <gnu/libc-version.h>
#include <linux/fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/syscall.h>
#include <unistd.h>

static struct option long_options[] = {
    {"help",    no_argument, NULL, 'h'},
    {"verbose", no_argument, NULL, 'v'},
    {0, 0, 0, 0}
};

void usage(int exit_code) {
    puts("Usage: exchange [-v] PATH1 PATH2\n"
         "  or:  exchange -h|--help\n"
         "atomically exchange names of two files or directories\n"
         "\n"
         "Options:\n"
         "  -h, --help      shows help text\n"
         "  -v, --verbose   produce verbose output");
    exit(exit_code);
}

int main(int argc, char **argv) {
    int c;
    bool verbose = false;
    char **paths;
    int ret;

    while ((c = getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
        switch (c) {
            case 'h':
                usage(EXIT_SUCCESS);
            case 'v':
                verbose = true;
                break;
            default:
                usage(EXIT_FAILURE);
        }
    }

    if (argc - optind != 2) {
        puts("Exactly two paths are required.\n");
        usage(EXIT_FAILURE);
    }

    paths = argv + optind;

    if (verbose) {
        printf("Exchanging paths %s and %s\n", paths[0], paths[1]);
    }

    // Atomically exchange the two paths. If paths are not absolute, consider
    // them relative to the current working directory
#if (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 28))
        ret = renameat2(AT_FDCWD, paths[0], AT_FDCWD, paths[1], RENAME_EXCHANGE);
#else
        ret = syscall(SYS_renameat2, AT_FDCWD, paths[0], AT_FDCWD, paths[1], RENAME_EXCHANGE);
#endif

    if (ret == -1) {
        perror("exchange: could not exchange the two paths");
        exit(EXIT_FAILURE);
    }

    if (verbose) {
        puts("Paths exchanged successfully");
    }

    return EXIT_SUCCESS;
}
