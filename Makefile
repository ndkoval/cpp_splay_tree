CC=g++
CFLAGS=-c -Wall
SOURCES=main.cpp splay_tree.h binary_tree.h tools.h

run: all
	./main

all: clean
	$(CC) $(SOURCES) -o main

clean:
	rm -rf *.o *.gch main
