#include <string>


class Matrix {
    class AccessProxy {
    public:
        AccessProxy(Matrix* m, size_t r);
        int& operator[](size_t column);

    private:
        Matrix* matrix;
        size_t row;
    };

    class ConstAccessProxy {
    public:
        ConstAccessProxy(const Matrix* m, size_t r);
        const int& operator[](size_t column) const;

    private:
        const Matrix* matrix;
        size_t row;
    };

public:
    Matrix(size_t, size_t);
    ~Matrix();

    size_t getRows();
    size_t getColumns();
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    Matrix& operator*=(const int& v);
    const ConstAccessProxy operator[](size_t i) const;
    AccessProxy operator[](size_t i);

private:
    size_t rows;
    size_t columns;
    size_t size;
    int *data;

    int& get(size_t, size_t);
    const int& get(size_t, size_t) const;
};
