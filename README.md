# exchange

Exchange two files in Linux.

## Example

```bash
echo a > a.txt
echo b > b.txt
exchange a.txt b.txt
cat a.txt   # b
cat b.txt   # a
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
