#include <iostream>
#include "threadpool.h"
#include "filesort.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Use: sort <infile> <outfile>";
        return 1;
    } else {
        std::string fromF{argv[1]};
        std::string toF{argv[2]};
        sortFile<uint64_t>(fromF, toF, 2, 8 * (2<<20) * 0.8);
    }
    return 0;
}
