CC=g++

all: build

run: build
	./sort in.file out.file 

build: sort.o 
	$(CC) -o sort sort.o

sort.o: sort.cpp filesort.h threadpool.h
	$(CC) -std=c++1z -c sort.cpp

test.o: test.cpp filesort.h threadpool.h
	$(CC) -std=c++1z  -c test.cpp

buid.test: test.o 
	$(CC)  -o test test.o

test: buid.test
	./test

clean:
	rm -rf *.o sort test