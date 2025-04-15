#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include "semaphore.hpp"

const int BUFFER_SIZE = 100;
const int NUM_ITEMS = 1000;


std::queue<int> buffer;
std::mutex buffer_mutex;
Semaphore empty_slots(BUFFER_SIZE);
Semaphore full_slots(0);

void producer() {
    for (int i = 0; i < NUM_ITEMS; ++i) {
       
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        empty_slots.wait();  
        
        {
            std::lock_guard<std::mutex> lock(buffer_mutex);
            buffer.push(i);
           
        }
        
        full_slots.signal(); 
    }
}

void consumer(int id) {
    for (int i = 0; i < NUM_ITEMS/2; ++i) {  
       
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        
        full_slots.wait();  
        
        int item;
        {
            std::lock_guard<std::mutex> lock(buffer_mutex);
            item = buffer.front();
            buffer.pop();
    
        }
        
        empty_slots.signal();  
    }
}

int main() {
  return 0;
}
