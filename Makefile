INCLUDES=-I.
CC=gcc
CFLAGS=-I. -c -g -Wall $(INCLUDES)
LINKARGS=-lm
LIBS=-lm

OBJECT_FILES = cmsc257-s17-assign2.o \
			cmsc257-s17-assign2-support.o

all : cmsc257-s17-assign2 

cmsc257-s17-assign2 : $(OBJECT_FILES)
	$(CC) $(LINKARGS) $(OBJECT_FILES) -o $@ $(LIBS)

cmsc257-s17-assign2.o : cmsc257-s17-assign2.c cmsc257-s17-assign2-support.h
	$(CC) $(CFLAGS) $< -o $@

cmsc257-s17-assign2-support.o : cmsc257-s17-assign2-support.c cmsc257-s17-assign2-support.h
	$(CC) $(CFLAGS) $< -o $@

clean : 
	rm -f cmsc257-s17-assign2 $(OBJECT_FILES)
