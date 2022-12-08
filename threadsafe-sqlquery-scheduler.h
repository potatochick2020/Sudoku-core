#include <iostream>
#include <queue>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

class threadSafeQueue {
    private:
        std::mutex lock;
        std::queue thSafeQueue;
        std::atomic<bool> end; // true if the queue is finish
    public:
        void addTask();
        void getTask();
        void setEndSignal(bool flag);
        void startInsert(std::chrono::microseconds sleepTime);
}

