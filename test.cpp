#include <thread>
#include <list>
#include <iostream>
#include <sys/time.h>

#include "my_mutex.hpp"

long getTime() {
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000000 + time.tv_usec;
}


namespace test {
    bool go = false;
    TTASMutex mutex;
    std::atomic<long int> time = {0};
    int i = 0;
    void foo() {
        while(!go);
        auto start = getTime();
        for(int k = 0; k < 1e6; ++k) {
            mutex.lock();
            test::i++;
            mutex.unlock();
        }
        time += getTime() - start;
    }
}



int main() {
    std::list<std::thread> list;
    for(int iter = 10; iter <= 200; iter+=10) {
        for(int i = 0; i < iter; i++) {
            list.push_back(std::thread(test::foo));
        } 
        test::go = true;

        for(auto& item : list) {
            item.join();
        }

        auto time = test::time.load() / (iter * 1e6);
        std::cout << iter << "    " << time << std::endl;
        test::time.store(0);
        list.clear();
        test::go = false;
    }
    return 0;
}
