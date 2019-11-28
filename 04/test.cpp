#include <iostream>
#include <string>
#include "matrix.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

int main() {

    Matrix m(10, 5);
    bool success = false;
    try {
        m[20][1] = 1;
    } catch (const std::out_of_range& e) {
        success = true;
    }
    std::cout <<"Check out of range access " << status(success) << std::endl;
    std::cout <<"Check getRows " << status(m.getRows() == 10) << std::endl;
    std::cout <<"Check getColumns " << status(m.getColumns() == 5) << std::endl;

    for (int row = 0; row < m.getRows(); ++row) {
        for (int col = 0; col < m.getColumns(); ++col) {
            m[row][col] = row + col;
        }
    }
    std::cout <<"Check access " << status(m[5][2] == 7) << std::endl;

    m *= 5;

    bool check = true;
    for (int row = 0; row < m.getRows(); ++row) {
        for (int col = 0; col < m.getColumns(); ++col) {
            check = check && (m[row][col] == (row + col)*5 );
        }
    }
    std::cout <<"Check *= " << status(check) << std::endl;

    Matrix &mref = m;
    std::cout <<"Check mref==m " << status(mref == m) << std::endl;

    Matrix m1(5, 3);
    Matrix m2(5, 3);
    Matrix m3(5, 5);

    std::cout <<"Check == " << status(m1 == m2) << std::endl;

    m2[0][0] = 5;
    std::cout <<"Check != " << status(m1 != m2) << std::endl;

    std::cout <<"Check diff size != " << status(m1 != m3) << std::endl;

    std::cout <<"Tests completed" << std::endl;
}
