#include "semaphore.hpp"

Semaphore::Semaphore(unsigned int initial_count) : count(initial_count) {}

void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return count > 0; });
    count--;
}

void Semaphore::signal() {
    std::lock_guard<std::mutex> lock(mtx);
    count++;
    cv.notify_one();
}
