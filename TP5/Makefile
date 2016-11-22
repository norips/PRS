CC := gcc
CFLAGS := -Wall -std=c99 -D_REENTRANT
LDLIBS :=  -lpthread -lm
SRC := $(wildcard *.c)
TARGET := $(SRC:%.c=bin/%)

all: | bin $(TARGET)
	
bin/% : %.c tools.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

tools.o : ../TP1/tool/tools.c ../TP1/tool/tools.h
	$(CC) $(CFLAGS) -c $< -o $@
bin:
	mkdir bin

clean:
	rm -fr bin/
