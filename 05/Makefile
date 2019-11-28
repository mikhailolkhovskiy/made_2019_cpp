CC=g++

all: build

run: build
	./main

build: buid.test

serialize.o: serialize.cpp serialize.h
	$(CC) -c serialize.cpp
	
test.o: test.cpp serialize.h
	$(CC) -c test.cpp

buid.test: test.o serialize.o 
	$(CC) -o test test.o serialize.o

test: buid.test
	./test

clean:
	rm -rf *.o test
