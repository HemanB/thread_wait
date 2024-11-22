CC = gcc
CFLAGS = -Wall -O2

PROGS =  array

all: $(PROGS)

array: array.c mythreads.h .thread_util.o
	$(CC) $(CFLAGS)  -o $@  $< .thread_util.o -lpthread

clean:
	rm -f $(PROGS)


