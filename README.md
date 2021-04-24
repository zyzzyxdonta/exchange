# exchange

Atomically exchange two files in Linux.

## Example

```bash
echo a > a.txt
echo b > b.txt
exchange a.txt b.txt
cat a.txt   # b
cat b.txt   # a
```

You can also exchange directories and symlinks, and the types of the two files don't have to match.

Observe that you are exchanging the names of the files; no new inodes are created:

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

If you want to install the program in a different location, you can do that by overriding the
variable `DEST`, e.g.:

```bash
make DEST=~/.local/bin install
```

## Details

`exchange` is essentially a wrapper around [renameat2](https://man7.org/linux/man-pages/man2/rename.2.html)
with the `RENAME_EXCHANGE` flag set.
Therefore, all its limitations hold for this program.
One important and not so obvious restriction that was pointed out to me is that the files to be
exchanged must exist on the same mount point.
