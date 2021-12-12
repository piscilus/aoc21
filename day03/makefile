src = $(wildcard *.c)
obj = $(src:.c=.o)

CC = gcc
CFLAGS  = -g -Wall

day03.exe: $(obj)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(obj) day03.exe
