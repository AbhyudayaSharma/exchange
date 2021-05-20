# Exchange file or directory names atomically

[![build](https://github.com/AbhyudayaSharma/exchange/actions/workflows/build.yml/badge.svg)](https://github.com/AbhyudayaSharma/exchange/actions/workflows/build.yml)

Wrapper over the Linux syscall `renameat2` with the `RENAME_EXCHANGE` flag set. For more
information, read [`man renameat2`](https://www.man7.org/linux/man-pages/man2/rename.2.html).

## Installing

This program only works on Linux. To compile:

```bash
make
```

To install to `/usr/local/bin`:

```bash
make install
```

## Usage

```text
exchange: exchange names of two files or directories atomically
Usage: exchange FILE1 FILE2 [flags...]
Allowed flags:
        --help:    shows this help text
        --verbose: produces verbose output
```
