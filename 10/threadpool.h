#pragma once
#include <atomic>
#include <future>
#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <iostream>

class ThreadPool
{
public:
    using Task = std::function<void ()>;

    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
    bool waitCompleted();
private:
    std::vector<std::thread> threads;
    std::queue<Task> tasks;
    std::mutex m;
    std::condition_variable hasTask;
    std::condition_variable finished;
    volatile bool stopped = false;
    std::atomic_int activeCount = 0;
};

ThreadPool::ThreadPool(size_t poolSize) {
    for (size_t i = 0; i < poolSize; ++i) {
        threads.emplace_back([this]() {
            while (true) {
                Task task;
                {
                    std::unique_lock<std::mutex> lock(m);
                    while (!stopped && tasks.empty()) {
                        hasTask.wait(lock);
                    }
                    if (stopped) {
                        return;
                    }
                    ++activeCount;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
                --activeCount;
                finished.notify_all();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m);
        stopped = true;
    }
    hasTask.notify_all();
    for(std::thread &t: threads) {
        t.join();
    }
}

bool ThreadPool::waitCompleted() {
    {
        std::unique_lock<std::mutex> lock(m);
        while (!stopped && (!tasks.empty() || activeCount.load() > 0)) {
            finished.wait(lock);
        }
    }
    return !stopped;
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    using ReturnType = typename std::result_of<Func(Args...)>::type;

    std::shared_ptr task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(func, args...));
    auto feature = task->get_future();
    {
        std::unique_lock<std::mutex> lock(m);
        tasks.emplace([task](){
            (*task)();
        });
        hasTask.notify_one();

    }
    return feature;
}

