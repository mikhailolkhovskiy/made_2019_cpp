#include <assert.h>
#include <iostream>
#include <string>
#include "calc.h"


void testSuccess(const std::string& str, int expectedResult) {
    try {
        Calculator c;
        int result = c.calc(str.c_str());
        if (expectedResult == result) {
            std::cout << "Pass: " << expectedResult << " == "
                      << result << "  "<< str;
        } else {
            std::cout << "Failure: " << expectedResult << " != "
                      << result << "  "<< str;
        }
    } catch (CalcException &e) {
        std::cout << "Failure: " << e.what() << " Pos:"
                  << e.getPosition() << "  "<< str;
    }
    std::cout << std::endl;
}

void testFailure(const std::string& str, int errorCode) {
    try {
        Calculator c;
        int result = c.calc(str.c_str());
        std::cout << "Failure: Expected error code" << errorCode <<"  "<< str;
    } catch (CalcException &e) {
        if (errorCode == e.getCode()) {
            std::cout << "Pass: \"" << e.what() << "\" Pos:"
                      << e.getPosition() << "  "<< str;
        } else {
            std::cout << "Failure: Error code " << errorCode << " != "
                      << e.getCode() << "  "<< str;
        }
    }
    std::cout << std::endl;
}


int main() {
    testSuccess("1+1", 2);
    testSuccess(" 1 + 1 ", 2);
    testSuccess("1+1--1", 3);
    testSuccess("1+1-2*4/2", -2);
    testSuccess("-1 + 2", 1);

    testFailure("", 2);
    testFailure("+", 2);
    testFailure("1+", 2);
    testFailure("---1", 2);
    testFailure("1+", 2);
    testFailure("3/0", 1);
    testFailure("X", 2);
    std::cout <<"Tests completed" << std::endl;
}
