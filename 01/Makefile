CC=g++

all: build

run: build
	./calc $(ARGS) 

build: main.o calc.o 
	$(CC) -o calc main.o calc.o

main.o: main.cpp calc.h
	$(CC) -c main.cpp

calc.o: calc.cpp calc.h
	$(CC) -c calc.cpp
	
test.o: test.cpp calc.o calc.h
	$(CC) -c test.cpp

buid.test: test.o calc.o 
	$(CC) -Wwrite-strings -o test test.o calc.o

test: buid.test
	./test

clean:
	rm -rf *.o calc test
