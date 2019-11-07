#include <iostream>
#include <string>
#include "linearalloc.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

int main() {
    LinearAllocator small(10);
    LinearAllocator large(1000);
    char* np = small.alloc(100);
    std::cout << "Allocate more than size: " << status(np == nullptr) << std::endl;

    char* p1 = small.alloc(1);
    std::cout << "Allocate one size: " << status(p1 != nullptr) << std::endl;

    char* p2 = large.alloc(1000);
    std::cout << "Allocate full size: " << status(p2 != nullptr) << std::endl;

    large.reset();
    char* p3 = large.alloc(1000);
    std::cout << "Reset and allocate full size: " << status(p3 != nullptr) << std::endl;

    char* p4 = small.alloc(1);
    char* p5 = small.alloc(1);
    std::cout << "Check linear allocation: " << status(p5-p4 == 1) << std::endl;

    std::cout <<"Tests completed" << std::endl;
}
