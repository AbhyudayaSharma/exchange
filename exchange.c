#define _GNU_SOURCE

#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static struct option long_options[] = {
    {"help",    no_argument, NULL, 'h'},
    {"verbose", no_argument, NULL, 'v'},
    {0, 0, 0, 0}
};

void usage(int exit_code) {
    puts("Usage: exchange [-v] PATH1 PATH2\n"
         "  or:  exchange -h|--help\n"
         "atomically exchange names and contents of two files or directories\n"
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

    while ((c = getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
        switch (c) {
            case 'h':
                usage(0);
            case 'v':
                verbose = true;
                break;
            default:
                usage(1);
        }
    }

    if (argc - optind != 2) {
        puts("Exactly two paths are required.\n");
        usage(1);
    }

    paths = argv + optind;

    if (verbose) {
        printf("Exchanging paths %s and %s\n", paths[0], paths[1]);
    }

    // Atomically exchange the two paths. If paths are not absolute, consider
    // them relative to the current working directory
    if (renameat2(AT_FDCWD, paths[0], AT_FDCWD, paths[1], RENAME_EXCHANGE) == -1) {
        perror("exchange: could not exchange the two paths");
        return 1;
    }

    if (verbose) {
        puts("Paths exchanged successfully");
    }

    return 0;
}
