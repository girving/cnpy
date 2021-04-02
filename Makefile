all: example

example: example.c npy.c npy.h
	$(CC) $(CFLAGS) -o $@ example.c npy.c
