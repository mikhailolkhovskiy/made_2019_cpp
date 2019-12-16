#include <iostream>
#include <functional>
#include "format.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

void checkThrow(std:: string msg, std::function<void()> func) {
    std::cout << msg << " ";
    try {
        func();
        std::cout << "Failed";
    } catch (std::runtime_error& e) {
        std::cout << "Passed";
    }
    std::cout << std::endl;
}

struct Test {
    int v;
};

std::ostream& operator<<(std::ostream& out, const Test& t) {
    out << t.v;
    return out;
}


int main() {
    std::cout << "Format empty str "
              << status(format("") == "") << std::endl;
    std::cout << "Format str "
              << status(format("1234ab") == "1234ab") << std::endl;
    std::cout << "Format {0} {0} "
              << status(format("{0} {0}", 1) == "1 1") << std::endl;
    std::cout << "Format {0} {1} "
              << status(format("{0} {1}", 1, 2) == "1 2") << std::endl;
    std::cout << "Format {1} {2} "
              << status(format("{1} {2}", 1, 2, 3) == "2 3") << std::endl;

    Test t{123};
    std::cout << "Format custom class "
              << status(format("{0}", t) == "123") << std::endl;
    checkThrow("Invalid placeholder {", [](){format("{0");});
    checkThrow("Invalid placeholder {1s}", [](){format("{1s}");});
    checkThrow("Out of range placeholder", [](){format("{0} {4}", 1, 2);});
    checkThrow("Unexpected }", [](){format("{0} }", 1);});
}
