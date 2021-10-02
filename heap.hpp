#include <math.h>
#include <random>
#include "queue.hpp"
#include "customer.hpp"
#ifndef HEAP_HPP
#define HEAP_HPP

class Heap {
    private:
        const int heapSize = 12;
        float currentTime; // keep track of ticks
        
    public:
        bool IsEmpty();
        Customer NextCustomer();
        void InsertCustomer(Customer newCustomer);
        void ConstructHeap(int initialSize);
        void PercolateDown(Customer newCustomer);
        void PercolateUp(Customer newCustomer);
        void BuildHeap();
        Customer events[13];
        float GetNextRandomInterval();
};


#endif