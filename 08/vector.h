#pragma once
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <type_traits>


template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T> {
public:

    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;

    explicit Iterator(T* p): ptr{p} {}
    Iterator& operator++() { ++ptr; return *this; }
    Iterator operator++(int) { auto tmp = *this; ++ptr; return tmp; }
    Iterator& operator--() { --ptr; return *this; }
    Iterator operator--(int) { auto tmp = *this; --ptr; return tmp; }
    Iterator& operator+=(difference_type x) { ptr += x; return *this; }
    Iterator& operator-=(difference_type x) { ptr -= x; return *this; }
    T& operator*() { return *ptr; }
    T& operator[](difference_type n) { return ptr[n]; }
    bool operator==(const Iterator& rhs) { return ptr == rhs.ptr; }
    bool operator!=(const Iterator& rhs) { return !(*this == rhs); }
private:
    T* ptr;
};

template <class T, class Alloc = std::allocator<T>>
class Vector {
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using allocator_type = Alloc;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<Iterator<T>>;
    const size_type MIN_VECTOR_SIZE = 10;

    explicit Vector(size_type count);
    Vector(size_type count, const value_type& defaultValue);
    Vector(std::initializer_list<value_type> init);
    ~Vector();

    iterator begin() noexcept;
    reverse_iterator rbegin() noexcept;
    iterator end() noexcept;
    reverse_iterator rend() noexcept;

    void push_back(value_type&& value);
    void push_back(const value_type& value);
    value_type back() const;
    void pop_back();

    void resize(size_type newSize);
    void resize(size_type newsize, const value_type& defaultValue);
    void reserve(size_type count);

    bool empty() const;
    size_type size() const;
    size_type capacity() const;
    size_type vector();
    void clear() noexcept;

    reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;
    bool operator==(const Vector<T> &rhs) const;
    bool operator!=(const Vector<T> &rhs) const;

private:
    void resizeIfNeeded();
    void resizeData(size_type);

    allocator_type alloc;
    size_type vectorCapacity;
    size_type vectorSize;
    value_type* data;
};

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count)
:   alloc{allocator_type()},
    vectorCapacity{count},
    vectorSize{count},
    data{alloc.allocate(count)}
{
    for (size_type i = 0; i < count; ++i) {
        std::allocator_traits<Alloc>::construct(alloc, data + i);
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count, const value_type& defaultValue)
:   alloc{allocator_type()},
    vectorCapacity{count},
    vectorSize{count},
    data{alloc.allocate(count)}
{
    for (size_type i = 0; i < count; ++i) {
        std::allocator_traits<Alloc>::construct(alloc, data + i, defaultValue);
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(std::initializer_list<value_type> init)
:   alloc{allocator_type()},
    vectorCapacity{init.size()},
    vectorSize{init.size()},
    data{alloc.allocate(init.size())}
{
    size_type i = 0;
    auto current = init.begin();
    const auto end = init.end();
    while (current != end) {
        std::allocator_traits<Alloc>::construct(alloc, data + i, *current++);
        ++i;
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::~Vector() {
    for (size_type i = 0; i < vectorSize; ++i) {
        std::allocator_traits<Alloc>::destroy(alloc, data + i);
    }
    alloc.deallocate(data, vectorCapacity);
}

template <class T, class Alloc>
bool Vector<T, Alloc>::operator==(const Vector<T> &rhs) const {
    if (this == &rhs) {
        return true;
    }
    if (vectorSize != rhs.vectorSize) {
        return false;
    }
    for (size_type i = 0; i < vectorSize; ++i) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

template <class T, class Alloc>
bool Vector<T, Alloc>::operator!=(const Vector<T> &rhs) const {
    return !(*this == rhs);
}


template <class T, class Alloc>
void Vector<T, Alloc>::push_back(value_type&& value) {
    if (vectorSize == vectorCapacity) {
        resizeData(2*vectorCapacity);
    }
    std::allocator_traits<Alloc>::construct(alloc, data + vectorSize, std::move(value));
    ++vectorSize;
}

template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const value_type& value) {
    if (vectorSize == vectorCapacity) {
        resizeData(2*vectorCapacity);
    }
    std::allocator_traits<Alloc>::construct(alloc, data + vectorSize, value);
    ++vectorSize;
}

template <class T, class Alloc>
void Vector<T, Alloc>::resizeIfNeeded() {
    float resizeK = 1;
    if (size < vectorCapacity/3) {
        resizeK = 0.5;
    } else if (size == vectorCapacity) {
        resizeK = 2;
    }

    resizeData(resizeK * vectorCapacity);
}

template <class T, class Alloc>
void Vector<T, Alloc>::resizeData(size_type newCapacity) {
    if (newCapacity == vectorCapacity && newCapacity < MIN_VECTOR_SIZE) {
        return;
    }
    T * newData = alloc.allocate(newCapacity);
    auto newVectorSize = std::min(vectorSize, newCapacity);
    for (size_type i = 0; i < newVectorSize; ++i) {
        std::allocator_traits<Alloc>::construct(alloc, newData + i, std::move(data[i]));
    }
    for (size_type i = 0; i < vectorSize; ++i) {
        std::allocator_traits<Alloc>::destroy(alloc, data + i);
    }
    alloc.deallocate(data, vectorCapacity);
    data = newData;
    vectorCapacity = newCapacity;
    vectorSize = newVectorSize;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::value_type Vector<T, Alloc>::back() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return data[vectorSize - 1];
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    if constexpr(!std::is_pod<value_type>::value) {
        std::allocator_traits<Alloc>::destroy(alloc, vectorSize - 1);
    }
    --vectorSize;
    resizeIfNeeded();
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(size_type newSize) {
    auto oldVectorSize = vectorSize;
    resizeData(newSize);
    for (size_type i = oldVectorSize; i < newSize; ++i) {
        std::allocator_traits<Alloc>::construct(alloc, data + i);
    }
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(size_type newSize, const value_type& defaultValue) {
    auto oldVectorSize = vectorSize;
    resizeData(newSize);
    for (size_type i = oldVectorSize; i < newSize; ++i) {
        std::allocator_traits<Alloc>::construct(alloc, data + i, defaultValue);
    }
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(size_type count) {
    if (vectorCapacity < count) {
        resizeData(count);
    }
}

template <class T, class Alloc>
bool Vector<T, Alloc>::empty() const {
    return vectorSize == 0;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::size() const {
    return vectorSize;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::capacity() const {
    return vectorCapacity;
}

template <class T, class Alloc>
void Vector<T, Alloc>::clear() noexcept {
    for (size_type i = 0; i < vectorSize; ++i) {
        std::allocator_traits<Alloc>::destroy(alloc, data + i);
    }
    vectorSize = 0;
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::operator[](size_type pos) {
    return data[pos];
}

template <class T, class Alloc>
constexpr typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::operator[](size_type pos) const {
    return data[pos];
}

template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::begin() noexcept {
    return iterator(data);
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin() noexcept {
    return std::make_reverse_iterator(end());
}

template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::end() noexcept {
    return iterator(data+vectorSize);
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend() noexcept {
    return std::make_reverse_iterator(begin());
}
