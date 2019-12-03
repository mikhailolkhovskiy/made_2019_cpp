#pragma once

#include <iostream>
#include <string>

class BigInt {
 public:
    BigInt(int64_t);
    BigInt(const BigInt&);
    BigInt(BigInt&&);
    ~BigInt();

    BigInt& operator=(const BigInt&);
    BigInt& operator=(BigInt&&);
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    BigInt operator+(const BigInt& other) const &;
    BigInt operator+(const BigInt& other) &&;
    BigInt operator+(BigInt&& other) const &;
    BigInt operator+(BigInt&& other) &&;
    BigInt operator-(const BigInt& other) const &;
    BigInt operator-(const BigInt& other) &&;
    BigInt operator-(BigInt&& other) const &;
    BigInt operator-(BigInt&& other) &&;
    BigInt operator-() const &;
    BigInt& operator-() &&;
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);

    std::string toString() const;

 private:
    void trimSize();
    size_t size;
    size_t buffSize;
    bool negative;
    char *buff;
};
std::ostream& operator<<(std::ostream& out, const BigInt& value);
