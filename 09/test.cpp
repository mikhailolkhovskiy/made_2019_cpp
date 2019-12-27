#include <iostream>
#include <vector>
#include <future>
#include "threadpool.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

int main() {
    {
        ThreadPool pool{2};
        auto func = [](int a, int b)->int {
            return a + b;
        };
        std::vector<std::shared_future<int>> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(pool.exec(func, 1, i));
        }
        std::vector<int> results;
        for (auto f : vec) {
            results.push_back(f.get());
        }
        std::vector<int> expectedResults = {1,2,3,4,5,6,7,8,9,10};
        std::cout <<"Checking queuing " << status(expectedResults == results) << std::endl;
        results.clear();
    }
    std::cout <<"Pool destruction Passed" << std::endl;
    std::cout <<"Tests completed" << std::endl;
}
