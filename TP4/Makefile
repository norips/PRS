CC := gcc
CFLAGS := -Wall -std=gnu99 -g
SRC := $(wildcard *.c)
TARGET := $(SRC:%.c=bin/%)

all: bin $(TARGET) safe execute 

safe : 
	cd safe_exec && $(MAKE) -f MakefileEx

execute : 
	cd execute_avant && $(MAKE) -f MakefileEx
	
bin/% : %.c tools.o
	$(CC) $(CFLAGS) $^ -o $@

tools.o : ../TP1/tool/tools.c ../TP1/tool/tools.h
	$(CC) $(CFLAGS) -c $< -o $@
bin:
	mkdir bin

clean:
	rm -fr bin/
	cd execute_avant && $(MAKE) -f MakefileEx clean
	cd safe_exec && $(MAKE) -f MakefileEx clean
