#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    unsigned int count;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Semaphore(unsigned int initial_count) : count(initial_count) {}

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        count--;
    }

    void signal() {
        std::lock_guard<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

#endif
