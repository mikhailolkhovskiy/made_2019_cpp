CC=g++

all: build

run: build
	./main

build: buid.test

serialize.o: bigint.cpp bigint.h
	$(CC) -c bigint.cpp
	
test.o: test.cpp bigint.h
	$(CC) -c test.cpp

buid.test: test.o bigint.o 
	$(CC) -o test test.o bigint.o

test: buid.test
	./test

clean:
	rm -rf *.o test
