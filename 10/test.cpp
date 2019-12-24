#include <iostream>
#include <random>
#include <limits>
#include "threadpool.h"
#include "filesort.h"

template <typename T>
bool checkFile(std::string fn, int count) {
    std::ifstream f(fn, std::ios::in | std::ios::binary);
    int n = 1;
    T value = 0;
    T nextValue = 0;
    f.read(reinterpret_cast<char*>(&value), sizeof(T));
    while (f.read(reinterpret_cast<char*>(&nextValue), sizeof(T))) {
        if (value > nextValue) {
            return false;
        }
        ++n;
    }
    return n == count;
}

template <typename T>
void generateFile(std::string filename, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> rand(0, std::numeric_limits<T>::max());
    std::ofstream fout(filename, std::ios::trunc | std::ios::binary);
    for (int i = 0; i < count; ++i) {
        T value = rand(gen);
        fout.write(reinterpret_cast<char*>(&value), sizeof(T));
    }

}

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

int main(int argc, char* argv[]) {
    std::string inFilename = "small.in";
    std::string outFilename = "small.out";
    int size = 1000;
    generateFile<uint64_t>(inFilename, size/sizeof(uint64_t));
    sortFile<uint64_t>(inFilename, outFilename, 2, size*2);
    std::cout <<"Check sort small file " << status(checkFile<uint64_t>(outFilename, size/sizeof(uint64_t))) << std::endl;
    std::remove(inFilename.c_str());
    std::remove(outFilename.c_str());

    inFilename = "big.in";
    outFilename = "big.out";
    size = 20 * 1000 * 1000;
    generateFile<uint64_t>(inFilename, size/sizeof(uint64_t));
    sortFile<uint64_t>(inFilename, outFilename, 2, 8 * 1000 * 1000);
    std::cout <<"Check sort big file " << status(checkFile<uint64_t>(outFilename, size/sizeof(uint64_t))) << std::endl;
    std::remove(inFilename.c_str());
    std::remove(outFilename.c_str());
}