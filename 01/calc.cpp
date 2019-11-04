#include "calc.h"
#include <string.h>
#include <cctype>
#include <cstdlib>


int Calculator::calc(const char *str) {
    curPosition = 0;
    input = str;

    int value = term();
    while (true) {
        switch (curToken.type) {
        case MINUS:
            value -= term();
            break;
        case PLUS:
            value += term();
            break;
        case END:
            return value;
        }
    }
    return value;
}

int Calculator::term() {
    int value = prim();
    while (true) {
        curToken = nextToken();
        if (curToken.type == MUL) {
            value *= prim();
        } else if (curToken.type == DIV) {
            int tmpPosition = curPosition;
            int d = prim();
            if (d == 0) {
                throw CalcException("Divide by 0", 1, tmpPosition);
            } else {
                value /= d;
            }
        } else {
            return value;
        }
    }
    return value;
}

int Calculator::prim(bool numberExpected) {
    int tmpPosition = curPosition;
    curToken = nextToken();
    switch (curToken.type) {
    case MINUS:
        if (numberExpected) {
            throw CalcException("Number expected", 2, tmpPosition);
        }
        return -prim(true);
    case NUMBER:
        return curToken.numberValue;
    default:
        throw CalcException("Number or '-' expected", 2, tmpPosition);
    }
}

Token Calculator::nextToken() {
    while (input[curPosition] != 0 && input[curPosition] == ' ') {
        ++curPosition;
    }
    char ch = input[curPosition];
    if (ch == 0) {
        return {END, 0};
    } else if (std::isdigit(ch)) {
        const int maxInt = 10;
        char buff[maxInt + 1];
        int k = 0;
        while (input[curPosition] &&
                std::isdigit(input[curPosition]) && k < maxInt) {
            buff[k] = input[curPosition];
            ++k;
            ++curPosition;
        }
        buff[k] = 0;
        int numberValue = std::atoi(buff);
        return {NUMBER, numberValue};
    } else {
        ++curPosition;
        switch (ch) {
        case '+':
            return {PLUS, 0};
        case '-':
            return {MINUS, 0};
        case '*':
            return {MUL, 0};
        case '/':
            return {DIV, 0};
        default:
            throw CalcException("Number or '+-*/' expected", 2, --curPosition);
        }
    }
}
