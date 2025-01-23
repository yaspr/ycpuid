CC=gcc
CFLAGS=-Wall -Wextra -g
OFLAGS=-O2

all: ycpuid

ycpuid: ycpuid.c
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@

clean:
	rm -Rf ycpuid
