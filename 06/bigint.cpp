#include "bigint.h"
#include <algorithm>

bool less(const char *o1, size_t n1, const char *o2, size_t n2) {
    if (n1 < n2) {
        return true;
    }
    if (n1 > n2) {
        return false;
    }
    for (size_t i = n1; i > 0; --i) {
        if (o1[i-1] > o2[i-1]) {
            return false;
        }
        if (o1[i-1] < o2[i-1]) {
            return true;
        }
    }
    return false;
}

void sum(const char *o1, size_t n1, const char *o2, size_t n2, char *result) {
    size_t maxN = n1 > n2 ? n1 : n2;
    char over = 0;
    char r = 0;
    for (size_t i = 0; i < maxN; ++i) {
        char v1 = (i < n1 ? o1[i] : 0) + over;
        char v2 = i < n2 ? o2[i] : 0;
        r = v1 + v2;
        over = r > 9 ? 1 : 0;
        result[i] = r % 10;
    }
    result[maxN] = over;
}

void sub(const char *o1, size_t n1, const char *o2, size_t n2, char *result) {
    size_t maxN = n1 > n2 ? n1 : n2;
    char bor = 0;
    char r = 0;
    for (size_t i = 0; i < maxN; ++i) {
        char v1 = (i < n1 ? o1[i] : 0) - bor;
        char v2 = i < n2 ? o2[i] : 0;
        if (v1 < v2) {
            bor = 1;
            v1 = 10 + v1;
        } else {
            bor = 0;
        }
        r = v1 - v2;
        result[i] = r;
    }
}


BigInt::BigInt(int64_t value)
:   size{0},
    buffSize{20},
    negative{false},
    buff{new char[buffSize]{0}}
{
    if (value == 0) {
        size = 1;
        return;
    }
    if (value < 0) {
        negative = true;
        value = -value;
    }
    if (value < 0)
    size = 0;
    while (value > 0) {
        buff[size] = value % 10;
        value /= 10;
        ++size;
    }
}

BigInt::~BigInt() {
    delete []buff;
}

BigInt::BigInt(const BigInt& other)
:   size{other.size},
    buffSize{other.size},
    negative{other.negative},
    buff{new char[other.buffSize]{0}}
{
    std::copy(other.buff, other.buff+other.size, buff);
}

BigInt::BigInt(BigInt&& other)
:   size{other.size},
    buffSize{other.size},
    negative{other.negative},
    buff{other.buff}
{
    other.buff = nullptr;
    other.buffSize = 0;
    other.buff = 0;
}

void BigInt::trimSize() {
    size = buffSize;
    while (size > 1 && buff[size-1] == 0) {
        --size;
    }
}

BigInt& BigInt::operator=(const BigInt& other) {
    char *tBuff = new char[other.buffSize]{0};
    std::copy(other.buff, other.buff+other.size, tBuff);
    delete []buff;
    buff = tBuff;
    size = other.size;
    buffSize = other.buffSize;
    negative = other.negative;
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) {
    delete []buff;
    buff = other.buff;
    size = other.size;
    buffSize = other.buffSize;
    negative = other.negative;
    other.buff = nullptr;
    other.size = 0;
    other.buffSize = 0;
    return *this;
}

bool BigInt::operator==(const BigInt& other) const {
    if (this == &other) {
        return true;
    }

    if (size != other.size || negative != other.negative) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        if (buff[i] != other.buff[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (negative && !other.negative) {
        return true;
    }
    if (!negative && other.negative) {
        return false;
    }
    if (negative) {
        return less(other.buff, other.size, buff, size);
    } else {
        return less(buff, size, other.buff, other.size);
    }
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(other < *this);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

BigInt BigInt::operator+(const BigInt& other) const & {
    BigInt tmp{*this};
    tmp += other;
    return tmp;
}

BigInt BigInt::operator+(const BigInt& other) && {
    BigInt tmp{std::move(*this)};
    tmp += other;
    return tmp;
}

BigInt BigInt::operator+(BigInt&& other) const & {
    BigInt tmp{std::move(other)};
    tmp += *this;
    return tmp;
}

BigInt BigInt::operator+(BigInt&& other) && {
    BigInt tmp{std::move(*this)};
    tmp += other;
    return tmp;
}

BigInt BigInt::operator-(const BigInt& other) const & {
    BigInt tmp{*this};
    tmp -= other;
    return tmp;
}

BigInt BigInt::operator-(const BigInt& other) && {
    BigInt tmp{std::move(*this)};
    tmp -= other;
    return tmp;
}

BigInt BigInt::operator-(BigInt&& other) const & {
    BigInt tmp{std::move(other)};
    tmp -= *this;
    tmp.negative = !tmp.negative;
    return tmp;
}

BigInt BigInt::operator-(BigInt&& other) && {
    BigInt tmp{std::move(*this)};
    tmp -= other;
    return tmp;
}

BigInt& BigInt::operator+=(const BigInt& other) {
    size_t newBuffSize = (size > other.size ? size : other.size) + 1;
    char *newBuff = new char[newBuffSize]{0};
    if (negative == other.negative) {
        sum(buff, size, other.buff, other.size, newBuff);
    } else {
        if (less(buff, size, other.buff, other.size)) {
            sub(other.buff, other.size, buff, size,  newBuff);
            negative = !negative;
        } else {
            sub(buff, size, other.buff, other.size, newBuff);
        }
    }
    delete []buff;
    buff = newBuff;
    buffSize = newBuffSize;
    trimSize();
    return *this;
}
BigInt& BigInt::operator-=(const BigInt& other) {
    size_t newBuffSize = (size > other.size ? size : other.size) + 1;
    char *newBuff = new char[newBuffSize]{0};
    if (negative == other.negative) {
        if (less(buff, size, other.buff, other.size)) {
            sub(other.buff, other.size, buff, size,  newBuff);
            negative = !negative;
        } else {
            sub(buff, size, other.buff, other.size, newBuff);
        }
    } else {
        sum(buff, size, other.buff, other.size, newBuff);
    }
    delete []buff;
    buff = newBuff;
    buffSize = newBuffSize;
    trimSize();
    return *this;
}

BigInt BigInt::operator-() const & {
    BigInt tmp{*this};
    tmp.negative = !negative;
    return tmp;
}

BigInt& BigInt::operator-() && {
    negative = !negative;
    return *this;
}

std::string BigInt::toString() const {
    std::string result;
    if (negative) {
        result += '-';
    }
    for (auto i = size; i > 0; --i) {
        result += '0' + buff[i-1];
    }
    return result;
}


std::ostream& operator<<(std::ostream& out, const BigInt& value) {
    out << value.toString();
    return out;
}
