#include <math.h>
#include <random>
#include <iostream>
#include "queue.hpp"
#include "customer.hpp"
#ifndef HEAP_HPP
#define HEAP_HPP

class Heap {
    private:
        
        float currentTime; // keep track of ticks
        int mu = 3;
        int lambda = 2;
    public:
        Heap();
        bool IsEmpty();
        Customer* NextCustomer();
        void InsertCustomer(Customer newCustomer);
        void ConstructHeap(int initialSize); // first arrivals
        void PercolateDown(int i); // done
        void PercolateUp(Customer newCustomer); // done
        void BuildHeap();
        Customer events[201];
        float GetNextRandomInterval(int avg);
        void DeleteMin();
        int heapSize;
};


#endif