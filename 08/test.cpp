#include <iostream>

#include "vector.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

int main() {
    Vector<int> v0(5, 0);
    Vector<int> v1(5);
    Vector<int> v2(5, 1);
    Vector<int> v3{1, 1, 1, 1, 1};
    std::cout <<"Check construct 1 " << status(v0 == v1) << std::endl;

    std::cout <<"Check construct 2 " << status(v2 == v3) << std::endl;

    v2.push_back(2);
    int t = 2;
    v3.push_back(t);
    std::cout <<"Check push_back and resize " << status(v2 == v3) << std::endl;
    std::cout <<"Check back " << status(v2.back() == 2) << std::endl;

    v2.clear();
    std::cout <<"Check clear " << status(v2.size() == 0 && v2.capacity() == 10) << std::endl;

    v3[0] = 10;
    std::cout <<"Check [] " << status(v3[0] == 10) << std::endl;

    size_t i = 0;
    bool ch1 = true;
    for (int a : v3) {
        ch1 = ch1 && (a == v3[i++]);
    }
    std::cout <<"Check iterator " << status(ch1) << std::endl;

    i = v3.size();
    bool ch2 = true;
    for (Vector<int>::reverse_iterator itr = v3.rbegin(); itr != v3.rend(); ++itr) {
        ch2 = ch2 && (*(itr) == v3[--i]);
    }
    std::cout <<"Check reverse iterator " << status(ch2) << std::endl;

    std::cout <<"Tests completed" << std::endl;
}
