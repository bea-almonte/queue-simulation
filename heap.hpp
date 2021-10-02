#include <math.h>
#include <random>
#include "queue.hpp"
#include "customer.hpp"
#ifndef HEAP_HPP
#define HEAP_HPP

class Heap {
    private:
        const int heapSize = 5;
        float currentTime; // keep track of ticks
        Customer events[6];
    public:
        bool IsEmpty();
        Customer NextCustomer();
        void InsertCustomer(Customer newCustomer);
        void ConstructHeap(int initialSize);
        void PercolateDown(Customer newCustomer);
        void PercolateUp(Customer newCustomer);
        void BuildHeap();
        float GetNextRandomInterval();
};


#endif