#include <cstddef>

class LinearAllocator {
public:
    LinearAllocator(size_t);
    ~LinearAllocator();
    char* alloc(size_t);
    void reset();
private:
    size_t maxSize;
    size_t size;
    char* buffer;
};
