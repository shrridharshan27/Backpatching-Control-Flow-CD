CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

all: build/backpatch

build/backpatch: src/backpatching.c
	mkdir -p build
	$(CC) $(CFLAGS) src/backpatching.c -o build/backpatch

run: all
	./build/backpatch

clean:
	rm -rf build *.exe
