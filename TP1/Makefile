CC := gcc
CFLAGS := -Wall -std=c99 -g
SRC := $(wildcard *.c)
TARGET := $(SRC:%.c=bin/%)

all: | bin $(TARGET)

bin/% : %.c tools.o
	$(CC) $(CFLAGS) $^ -o $@

tools.o : tool/tools.c tool/tools.h
	$(CC) $(CFLAGS) -c $< -o $@
bin:
	mkdir bin

clean:
	rm -fr bin/
