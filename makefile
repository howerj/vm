CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -O2
TARGET=vm

.PHONY: run clean

all: ${TARGET}

%.out: %.pas pas
	./pas %.pas %.out

run: ${TARGET}
	./${TARGET} -D -x -c 10 -k test.hex

clean:
	rm -fv ${TARGET} pas *.o *.a *.exe
