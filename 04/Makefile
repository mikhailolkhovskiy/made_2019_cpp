CC=g++

all: build

run: build
	./main

build: buid.test

matrix.o: matrix.cpp matrix.h
	$(CC) -c matrix.cpp
	
test.o: test.cpp matrix.h
	$(CC) -c test.cpp

buid.test: test.o matrix.o 
	$(CC) -o test test.o matrix.o

test: buid.test
	./test

clean:
	rm -rf *.o test
