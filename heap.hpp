#include <math.h>
#include <random>
#include "queue.hpp"
#include "customer.hpp"
#ifndef HEAP_HPP
#define HEAP_HPP

class Heap {
    private:
        int heapSize;
        float currentTime; // keep track of ticks
    public:
        Heap() {
            heapSize = 11;
            currentTime = 0;
        };
        bool IsEmpty();
        Customer NextCustomer();
        void InsertCustomer(Customer newCustomer);
        void ConstructHeap(int initialSize);
        void PercolateDown(int i);
        void PercolateUp(Customer newCustomer); // done
        void BuildHeap(); // done
        Customer events[15];
        float GetNextRandomInterval();
        void DeleteMin();
};


#endif