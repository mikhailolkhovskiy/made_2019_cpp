CC=g++

all: build

run: build
	./main

build: main.o linearalloc.o 
	$(CC) -o main main.o linearalloc.o

main.o: main.cpp linearalloc.h
	$(CC) -c main.cpp

linearalloc.o: linearalloc.cpp linearalloc.h
	$(CC) -c linearalloc.cpp
	
test.o: test.cpp linearalloc.h
	$(CC) -c test.cpp

buid.test: test.o linearalloc.o 
	$(CC) -o test test.o linearalloc.o

test: buid.test
	./test

clean:
	rm -rf *.o main test
