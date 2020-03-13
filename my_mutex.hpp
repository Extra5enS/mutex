#pragma once
#include <atomic>

class MutexInterface {
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

class TTASMutex : public MutexInterface {
    std::atomic<unsigned> lockIter;
public:
    TTASMutex();
    void lock();
    void unlock();
};
 

class TicketMutex : public MutexInterface {
    std::atomic_size_t newServing;
    std::atomic_size_t nextTicket;
public:
    TicketMutex();
    void lock();
    void unlock();
};
