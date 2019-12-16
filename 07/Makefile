CC=g++

all: build

run: build
	./main

build: buid.test

format.o: format.cpp format.h
	$(CC) -c format.cpp
	
test.o: test.cpp format.h
	$(CC) -c test.cpp

buid.test: test.o format.o 
	$(CC) -o test format.o test.o 

test: buid.test
	./test

clean:
	rm -rf *.o test
