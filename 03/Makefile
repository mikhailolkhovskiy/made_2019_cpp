CC=g++

all: build

run: build
	./main

build: main.o parser.o 
	$(CC) -o main main.o parser.o

main.o: main.cpp parser.h
	$(CC) -c main.cpp

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp
	
test.o: test.cpp parser.h
	$(CC) -c test.cpp

buid.test: test.o parser.o 
	$(CC) -o test test.o parser.o

test: buid.test
	./test

clean:
	rm -rf *.o main test
