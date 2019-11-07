#include <iostream>
#include "linearalloc.h"

int main(int argc, char* argv[]) {
    LinearAllocator allocator(10);
    char *a = allocator.alloc(1);
    char *b = allocator.alloc(1);
    *a = 1;
    *b = 2;
    std::cout << *a + *b << std::endl;
}
