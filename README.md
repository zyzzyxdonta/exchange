# Moved to GitLab

https://gitlab.com/zyzzyxdonta/exchange

---

# exchange

Atomically exchange two files on Linux or Mac.

## Example

```bash
echo a > a.txt
echo b > b.txt
exchange a.txt b.txt
cat a.txt   # b
cat b.txt   # a
```

The types of the files don't have to match.
You could also exchange e.g. a file and a directory, or a symlink and a pipe.

Only the names of the files are swapped; no new inodes are created:

```bash
touch file1 file2
ls -i   # 26214612 file1  26214667 file2
exchange file1 file2
ls -i   # 26214667 file1  26214612 file2
```

## Installation

Build the program and install it to `/usr/local/bin`:

```bash
make
sudo make install
```

If you want to install the program in a different location, you can do so by overriding the `DEST`
variable, e.g.:

```bash
make DEST=~/.local/bin install
```

## Implementation

`exchange` is a simple wrapper around a library call.
On Linux, [`renameat2`](https://man7.org/linux/man-pages/man2/rename.2.html) with the
`RENAME_EXCHANGE` flag is used.
On Mac, the equivalent function is `renameatx_np` and the flag is called `RENAME_SWAP`.

The limitations of these functions depend on your OS and filesystem.
For more information, please refer to your system's man pages, i.e.

```bash
man 2 renameat2     # on Linux
man 2 renameatx_np  # on Mac
```
