#include <iostream> // for debag

#include "my_mutex.hpp"

TicketMutex::TicketMutex() : newServing(0), nextTicket(0) {}


void TicketMutex::lock() {

}


void TicketMutex::unlock() {

}


TTASMutex::TTASMutex() : lockIter(0) {}


void TTASMutex::lock() {
    unsigned expected = 0;
    do {
        while(lockIter.load()); // need to reduce nubmer rewriting the KEF
        expected = 0;

    } while ( !lockIter.compare_exchange_weak(expected, 1) );

}


void TTASMutex::unlock() {
    lockIter.store(0);
}


