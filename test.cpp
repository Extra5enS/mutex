#include <thread>
#include <list>
#include <iostream>

#include "my_mutex.hpp"

class TimeTestThread : public thread {
    
}

namespace test {
    TTASMutex mutex;
    int i = 0;
    void foo() {
        for(int k = 0; k < 1e6; ++k) {
            mutex.lock();
            ++i;
            mutex.unlock();
        }
    }
}



int main() {
    std::list<std::thread> list;    
    for(int i = 0; i < 1e1; i++) {
        list.push_back(std::thread(test::foo));
    }
    
    for(auto& item : list) {
        item.join();
    }

    std::cout << "The i is " << test::i << std::endl;

    return 0;
}
