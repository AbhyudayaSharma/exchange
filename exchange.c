#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printHelp() {
    puts("exchange: exchange names of two files or directories atomically\n"
         "Usage: exchange FILE1 FILE2 [flags...]\n"
         "Allowed flags:\n"
         "\t--help:    shows this help text\n"
         "\t--verbose: produces verbose output");
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printHelp();
        return 1;
    }

    bool verbose = false;
    for (int i = 3; i < argc; i++) {
        if (!strcmp(argv[i], "--verbose")) {
            verbose = true;
        } else if (!strcmp(argv[i], "--help")) {
            printHelp();
            return 0;
        } else {
            printf("Unrecognized flag: %s", argv[i]);
            return 1;
        }
    }

    if (verbose) {
        printf("Exchanging names: %s and %s\n", argv[1], argv[2]);
    }

    // atomically exchange the two directories
    // if paths are not absolute, consider them relative to the current working directory
    if(renameat2(AT_FDCWD, argv[1], AT_FDCWD, argv[2], RENAME_EXCHANGE) == -1) {
        perror("exchange: could not exchange the two paths");
        return 1;
    }

    if (verbose) {
        puts("Names exchanged successfully");
    }

    return 0;
}
