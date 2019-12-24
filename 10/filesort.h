#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <algorithm>
#include <exception>
#include <cstdio>

std::streamsize getFileSize(std::ifstream& file) {
    file.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize size = file.gcount();
    file.clear();
    file.seekg(0, std::ios_base::beg);
    return size;
}

template <typename T>
void sortChunk(std::string filename) {
    std::vector<T> vec;
    {
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        vec.resize(getFileSize(file)/sizeof(T));
        file.read(reinterpret_cast<char*>(&vec[0]), vec.size()*sizeof(T));
    }
    std::sort(vec.begin(), vec.end());
    std::ofstream fout(filename, std::ios::trunc | std::ios::binary);
    fout.write(reinterpret_cast<char*>(&vec[0]), vec.size()*sizeof(T));
}

template <typename T>
void mergeChunks(std::string filename1, std::string filename2, std::string filename) {
    std::ifstream f1(filename1, std::ios::in | std::ios::binary);
    std::ifstream f2(filename2, std::ios::in | std::ios::binary);
    std::ofstream fout(filename, std::ios::out | std::ios::binary);
    T v1 = 0;
    T v2 = 0;

    bool f1Empty = !(f1.read(reinterpret_cast<char*>(&v1), sizeof(T)));
    bool f2Empty = !(f2.read(reinterpret_cast<char*>(&v2), sizeof(T)));
    while (!f1Empty && !f2Empty) {
        while (v1 <= v2 && !f1Empty) {
            fout.write(reinterpret_cast<char*>(&v1), sizeof(T));
            f1Empty = !(f1.read(reinterpret_cast<char*>(&v1), sizeof(T)));
        }
        while (v2 <= v1 && !f2Empty) {
            fout .write(reinterpret_cast<char*>(&v2), sizeof(T));
            f2Empty = !(f2.read(reinterpret_cast<char*>(&v2), sizeof(T)));
        }
    }
    if (!f1Empty) {
        fout.write(reinterpret_cast<char*>(&v1), sizeof(T));
    }
    if (!f2Empty) {
        fout.write(reinterpret_cast<char*>(&v2), sizeof(T));
    }
    while (f1.read(reinterpret_cast<char*>(&v1), sizeof(T))) {
        fout.write(reinterpret_cast<char*>(&v1), sizeof(T));
    }
    while (f2.read(reinterpret_cast<char*>(&v2), sizeof(T))) {
        fout.write(reinterpret_cast<char*>(&v2), sizeof(T));
    }
    fout.flush();
    f1.close();
    f2.close();
    std::remove(filename1.c_str());
    std::remove(filename2.c_str());
}

template <typename T>
void sortFile(std::string& fromFile, std::string& toFile, size_t threadsCount, std::streamsize memLimit) {
    std::ifstream file(fromFile, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open " + fromFile);
    } else {
        std::streamsize fileSize = getFileSize(file);
        if (fileSize < memLimit) {
            std::vector<T> vec;
            vec.resize(fileSize/sizeof(T));
            file.read(reinterpret_cast<char*>(&vec[0]),  vec.size()*sizeof(T));
            std::sort(vec.begin(), vec.end());
            std::ofstream fout(toFile, std::ios::out | std::ios::binary);
            fout.write(reinterpret_cast<char*>(&vec[0]), vec.size()*sizeof(T));
        } else {
            std::vector<std::string> files;
            std::streamsize maxSize = (memLimit / threadsCount / sizeof(T)) * sizeof(T);
            {
                std::unique_ptr<char[]> buffer(new char[maxSize]);
                while (!file.eof()) {
                    std::string fName = "tmpSort" + std::to_string(files.size());
                    files.push_back(fName);
                    std::ofstream oFile(files.back());
                    file.read(buffer.get(), maxSize);
                    oFile.write(buffer.get(), file.gcount());
                    oFile.close();
                }
            }
            ThreadPool tPool{threadsCount};
            for (auto fn : files) {
                tPool.exec(sortChunk<T>, fn);
            }
            tPool.waitCompleted();
            int mergeStep = 0;
            while (files.size() > 2) {
                std::vector<std::string> v;
                for (size_t i = 0; i < (files.size()/2)*2; i+=2) {
                    std::string f1 = files[i];
                    std::string f2 = files[i + 1];
                    std::string fName = "tmpMerge" + std::to_string(mergeStep) + "_" + std::to_string(v.size());
                    v.push_back(fName);
                    tPool.exec(mergeChunks<T>, f1, f2, v.back());
                }
                if (files.size() % 2 == 1) {
                    v.push_back(files.back());
                }
                tPool.waitCompleted();
                files.swap(v);
                ++mergeStep;
            }
            mergeChunks<T>(files.front(), files.back(), toFile);
        }
    }
}
