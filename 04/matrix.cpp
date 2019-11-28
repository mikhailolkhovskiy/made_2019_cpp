#include "matrix.h"
#include <cctype>
#include <stdexcept>


Matrix::AccessProxy::AccessProxy(Matrix* m, size_t r)
    : matrix{m}
    , row{r}
{}

int& Matrix::AccessProxy::operator[](size_t column) {
    return matrix->get(row, column);
}

Matrix::ConstAccessProxy::ConstAccessProxy(const Matrix* m, size_t r)
    : matrix{m}
    , row{r}
{}

const int& Matrix::ConstAccessProxy::operator[](size_t column) const {
    return matrix->get(row, column);
}

Matrix::Matrix(size_t r, size_t c)
    : rows{r}
    , columns{c}
    , size{r*c}
    , data{new int[r*c]()}
{}

Matrix::~Matrix() {
    delete []data;
}

size_t Matrix::getRows() {
    return rows;
}

size_t Matrix::getColumns() {
    return columns;
}

bool Matrix::operator==(const Matrix& other) const {
    if (this == &other) {
        return true;
    }

    if (rows != other.rows || columns != other.columns) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix& Matrix::operator*=(const int& v) {
    for (size_t i = 0; i < size; ++i) {
        data[i] *= v;
    }
    return *this;
}

const Matrix::ConstAccessProxy Matrix::operator[](size_t i) const {
    return Matrix::ConstAccessProxy(this, i);
}

Matrix::AccessProxy Matrix::operator[](size_t i) {
    return Matrix::AccessProxy(this, i);
}

int& Matrix::get(size_t row, size_t column) {
    if (row >= rows || column >= columns) {
        throw std::out_of_range("Index is out of range");
    }
    return data[row*columns + column];
}

const int& Matrix::get(size_t row, size_t column) const {
    if (row >= rows || column >= columns) {
        throw std::out_of_range("Index is out of range");
    }
    return data[row*columns + column];
}


