CC=g++

all: build

build: buid.test
	
test.o: test.cpp vector.h
	$(CC) -std=c++1z -c test.cpp

buid.test: test.o
	$(CC) -o test test.o

test: buid.test
	./test

clean:
	rm -rf *.o test
