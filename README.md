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
exchange: atomically exchange names and contents of two files or directories
Usage: exchange [OPTIONS] PATH1 PATH2

Options:
        --help     show help text and exit
        --verbose  produces verbose output
```
