#include <limits>
#include "bigint.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

int main() {
    BigInt a{-10};
    BigInt a1{5};
    BigInt b{a};
    BigInt c = a;
    BigInt d = 15;

    std::cout << "Constructor negative: "
              << status(a.toString() == "-10") << std::endl;
    std::cout << "Constructor positive: "
              << status(a1.toString() == "5") << std::endl;
    std::cout << "Constructor copy: "
              << status(b.toString() == "-10") << std::endl;
    std::cout << "Operator =: "
              << status(c.toString() == "-10") << std::endl;
    std::cout << "Operator ==: "
              << status(a == b) << std::endl;
    std::cout << "Operator ==: "
              << status(!(a == 20)) << std::endl;
    std::cout << "Operator !=: "
              << status(a != a1) << std::endl;
    std::cout << "Operator !=: "
              << status(!(a != c)) << std::endl;
    std::cout << "Operator <: "
              << status(a < 0) << std::endl;
    std::cout << "Operator >: "
              << status(a > -15) << std::endl;
    std::cout << "Operator <=: "
              << status(a <= 0) << std::endl;
    std::cout << "Operator <=: "
              << status(a <= -10) << std::endl;
    std::cout << "Operator <=: "
              << status(!(a <= -100)) << std::endl;
    std::cout << "Operator >=: "
              << status(a >= -11) << std::endl;
    std::cout << "Operator >=: " << status(a >= -10) << std::endl;
    std::cout << "Operator >=: "
              << status(!(a >= 1)) << std::endl;
    std::cout << "Operator +=: "
              << status((a+=5).toString() == "-5") << std::endl;
    std::cout << "Operator +=: "
              << status((a+=-5).toString() == "-10") << std::endl;
    std::cout << "Operator +=: "
              << status((a+=20).toString() == "10") << std::endl;
    std::cout << "Operator -=: "
              << status((a-=5).toString() == "5") << std::endl;
    std::cout << "Operator -=: "
              << status((a-=-5).toString() == "10") << std::endl;
    std::cout << "Operator -=: "
              << status((a-=20).toString() == "-10") << std::endl;
    std::cout << "Operator -: "
              << status((a - d).toString() == "-25") << std::endl;
    std::cout << "Operator -: "
              << status((d - a).toString() == "25") << std::endl;
    std::cout << "Operator +: "
              << status((a + a1).toString() == "-5") << std::endl;
    std::cout << "Operator +: "
              << status((a + d).toString() == "5") << std::endl;

    BigInt big = std::numeric_limits<int64_t>::max();
    std::cout <<"Max int: "
              << status(big.toString() == "9223372036854775807") << std::endl;
    std::cout <<"2 Max int: "
              << status((big + big).toString() == "18446744073709551614")
              << std::endl;
}
