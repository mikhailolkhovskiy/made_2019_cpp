#pragma once

#include <string>
#include <iostream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out(out)
    {
    }

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args) {
        process(args...);
        return Error::NoError;
    }

private:
    std::ostream& out;

    template <class T, class... Args>
    void process(T val, Args... args) {
        process_one(val);
        process(args...);
    }

    template <class T>
    void process(T val) {
        process_one(val);
    }

    void process_one(bool val) {
        out << (val?"true":"false") << ' ';
    }

    void process_one(uint64_t val) {
        out << val << ' ';
    }
};

class Deserializer {
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in(in)
    {
    }

    template <class T>
    Error load(T& object) {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT& ... args) {
        return process(args...);
    }

private:
    std::istream& in;

    template <class T, class... Args>
    Error process(T& val, Args&... args) {
        auto err = process(val);
        if (err != Error::NoError) {
            return err;
        }
        return process(args...);
    }
    Error process(uint64_t&);
    Error process(bool&);
};
