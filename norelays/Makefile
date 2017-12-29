OBJS = main.o book.o utils.o
CFLAGS = -std=c99 -Wall
CC = gcc

all:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

.c.o:
	$(CC) -c $(CFLAGS) $< -o $*.o

.PHONY: clean

clean:
	@- rm $(OBJS) main

