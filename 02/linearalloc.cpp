#include "linearalloc.h"



LinearAllocator::LinearAllocator(size_t n)
:   maxSize {n},
    size {0},
    buffer {new char[n]}
{
}

LinearAllocator::~LinearAllocator() {
    delete [] buffer;
}

void LinearAllocator::reset() {
    size = 0;
}

char* LinearAllocator::alloc(size_t n) {
    if (size + n <= maxSize) {
        char* result = buffer + size;
        size += n;
        return result;
    } else {
        return nullptr;
    }
}
