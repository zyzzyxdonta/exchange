CC    = cc
FLAGS = -Wall -Wextra -O3

PROGRAM = exchange
DEST    = /usr/local/bin

$(PROGRAM): %: %.c
	$(CC) $(FLAGS) $^ -o $@

.PHONY: clean install

clean:
	rm -f $(PROGRAM)

install: $(PROGRAM)
	install -s $(PROGRAM) $(DEST)
