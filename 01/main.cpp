#include <iostream>
#include "calc.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Use: calc \"expression\"";
        return 1;
    } else {
        try {
            Calculator c;
            std::cout << c.calc(argv[1]);
            return 0;
        } catch (CalcException &e) {
            std::cout << argv[1] << std::endl;
            std::cout << e.what();
            std::cout << " Code:" << e.getCode();
            std::cout << " Position:" << e.getPosition() << std::endl;
        }
    }
}
