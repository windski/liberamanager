CC = gcc

OBJS = main.o book.o

.PHONY: clean

all: $(OBJS)
	$(CC) $(OBJS) -o main

.c.o:
	$(CC) -c $< -o $*.o


clean:
	-@ rm $(OBJS) main

