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
    Semaphore(unsigned int initial_count);
    void wait();
    void signal();
};

#endif
